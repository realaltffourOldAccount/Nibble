#include "TextRenderer.h"
#include <stdlib.h>

namespace GEngine {
namespace Text {
void TextRenderer::Init(void) {
	if (FT_Init_FreeType(&ft)) {
		THROW_ERROR(
			"Could not Initialize Freetype.",
			Log::GenLogID(__LINE__, __FILE__, "TextRenderer", __func__));
	}

#if defined(__DESKTOP__)
	t_Shaders = new GEngine::Shader("glsl/text_vs.glsl", "glsl/text_fs.glsl");
#elif defined(__WEB__)
	t_Shaders = new GEngine::Shader("glsl/text_vs_es_em.glsl",
									"glsl/text_fs_es_em.glsl");
#elif defined(__ANDROID__)
	t_Shaders =
		new GEngine::Shader("glsl/text_vs_es.glsl", "glsl/text_fs_es.glsl");
#endif

	t_VBO = new GEngine::VBO(GL_DYNAMIC_DRAW, sizeof(GLfloat) * 6 * 4, NULL);

	GEngine::ShaderAttrib attrib_pos;
	attrib_pos._index = 0;
	attrib_pos._size = 4;
	attrib_pos._type = GL_FLOAT;
	attrib_pos._isNorm = false;
	attrib_pos._stride = 4 * sizeof(GLfloat);
	attrib_pos._offset = 0;
	attrib_pos._isEnable = true;

	std::vector<GEngine::ShaderAttrib*> attribs = {&attrib_pos};

	t_VAO = new GEngine::VAO(t_VBO, attribs);
}
void TextRenderer::DeInit(void) {
	UnLoadAllCharacters();
	UnLoadAllFonts();

	if (t_Shaders != nullptr) {
		delete t_Shaders;
		t_Shaders = nullptr;
	}
	if (t_VBO != nullptr) {
		delete t_VBO;
		t_VBO = nullptr;
	}
	if (t_VAO != nullptr) {
		delete t_VAO;
		t_VAO = nullptr;
	}
}

void TextRenderer::LoadFont(std::string fontname, std::string fontPath) {
	FT_Face face;

#if defined(__ANDROID__)
	ANativeActivity* activity = glfmAndroidGetActivity();
	AAssetManager* manager = NULL;
	if (activity) {
		manager = activity->assetManager;
	}
	AAsset* fontFile =
		AAssetManager_open(manager, fontPath.c_str(), AASSET_MODE_BUFFER);
	off_t fontDataSize = AAsset_getLength(fontFile);

	char* fontData = new char[fontDataSize];
	int redres = AAsset_read(fontFile, fontData, (size_t)fontDataSize);
	AAsset_close(fontFile);
	FT_Error res =
		FT_New_Memory_Face(ft, (FT_Byte*)&fontData[0], fontDataSize, 0, &face);
#else
	FT_Error res = FT_New_Face(ft, fontPath.c_str(), 0, &face);
#endif

	if (0 != res) {
		THROW_ERROR(
			"Failed to load font name: " + fontname + ".",
			Log::GenLogID(__LINE__, __FILE__, "TextRenderer", __func__));
	}
	FT_Set_Pixel_Sizes(face, 0, 24);

	t_Fonts.insert(std::pair<std::string, FT_Face>(fontname, face));
}
void TextRenderer::UnLoadFont(std::string fontname) {
	auto font = t_Fonts.find(fontname);
	FT_Done_Face(font->second);
	t_Fonts.erase(fontname);
}
void TextRenderer::UnLoadAllFonts(void) {
	for (auto i = t_Fonts.begin(); i != t_Fonts.end(); i++)
		FT_Done_Face(i->second);

	t_Fonts.clear();
}

void TextRenderer::LoadCharacters(std::string fontname) {
	FT_Face face;
	auto loc = t_Fonts.find(fontname);
	if (loc != t_Fonts.end())
		face = t_Fonts[fontname];
	else {
		THROW_ERROR(
			"No " + fontname + " font name exists.",
			Log::GenLogID(__LINE__, __FILE__, "TextRenderer", __func__));
	}

	std::map<GLchar, Character> characters;
	GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
	for (GLubyte c = 32; c < 127; c++) {  // 127
		// Load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			Log::warn(
				"Could not load glyph for '" + std::to_string(c) +
					"' character.",
				Log::GenLogID(__LINE__, __FILE__, "TextRenderer", __func__));
			continue;
		}
		// Generate texture
		GEngine::TextureProps texProp;
		texProp._level = 0;
		texProp._width = face->glyph->bitmap.width;
		texProp._height = face->glyph->bitmap.rows;
		texProp._border = 0;
		texProp._type = GL_UNSIGNED_BYTE;
		texProp._data = face->glyph->bitmap.buffer;
		texProp._wrapS = GL_CLAMP_TO_EDGE;
		texProp._wrapT = GL_CLAMP_TO_EDGE;
		texProp._min_filter = GL_LINEAR;
		texProp._mag_filter = GL_LINEAR;
		texProp._gen_mipmap = false;
#if defined(__WEB__)
		texProp._internalFormat = GL_LUMINANCE;
		texProp._bufferFormat = GL_LUMINANCE;
#else
		texProp._internalFormat = GL_RED;
		texProp._bufferFormat = GL_RED;
#endif

		GEngine::Texture* texture = new GEngine::Texture(texProp);
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			static_cast<GLuint>(face->glyph->advance.x)};
		characters.insert(std::pair<GLchar, Character>(c, character));
	}
	GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 4));

	t_Characters.insert(
		std::pair<std::string, CHARS_LIST>(fontname, characters));
}
void TextRenderer::UnLoadCharacters(std::string fontname) {
	auto chars = t_Characters.find(fontname);
	for (auto i = chars->second.begin(); i != chars->second.end(); i++) {
		delete i->second._textureID;
		i->second._textureID = nullptr;
	}

	t_Characters.erase(fontname);
}
void TextRenderer::UnLoadAllCharacters(void) {
	for (auto i = t_Characters.begin(); i != t_Characters.end(); i++) {
		auto list = i->second;
		for (auto j = list.begin(); j != list.end(); j++) {
			delete j->second._textureID;
			j->second._textureID = nullptr;
		}
	}
	t_Characters.clear();
}

void TextRenderer::RenderText(std::string text, std::string fontname,
							  GLfloat scale, GEngine::Point location,
							  glm::vec3 color, GEngine::MVP* mvp) {
	glm::mat4 old_view = mvp->getView();
	glm::mat4 old_model = mvp->getModel();
	mvp->updateModel(glm::mat4(1.0f));
	mvp->updateView(glm::mat4(1.0f));

	t_Shaders->bind();
	mvp->bind(t_Shaders->getProgId());
	GLCall(
		glUniform3f(glGetUniformLocation(t_Shaders->getProgId(), "textColor"),
					color.x, color.y, color.z));

	t_VAO->bind();
	t_VBO->bind();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		Character ch = t_Characters[fontname][*c];
		if (ch._textureID == nullptr) continue;

		// Caculate character position.
		GLfloat xpos = location.x + ch._bearing.x * scale;
		GLfloat ypos = location.y - (ch._size.y - ch._bearing.y) * scale;

		GLfloat w = ch._size.x * scale;
		GLfloat h = ch._size.y * scale;

		// Update VBO for each character.
		GLfloat vertices[6][4] = {
			{xpos, ypos + h, 0.0, 0.0},	{xpos, ypos, 0.0, 1.0},
			{xpos + w, ypos, 1.0, 1.0},

			{xpos, ypos + h, 0.0, 0.0},	{xpos + w, ypos, 1.0, 1.0},
			{xpos + w, ypos + h, 1.0, 0.0}};

		// Render glyph texture over quad.
		ch._textureID->bind();
		// Update content of VBO memory.
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
		// Render quad
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
		ch._textureID->unbind();

		// Now advance cursors for next glyph (note that advance is number of
		// 1/64 pixels).
		location.x +=
			(ch._advance >> 6) *
			scale;  // Bitshift by 6 to get value in pixels (2^6 = 64).
	}
	t_VAO->unbind();
	t_VBO->unbind();
	t_Shaders->unbind();

	mvp->updateModel(old_model);
	mvp->updateView(old_view);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}
}  // namespace Text
}  // namespace GEngine