#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H
#pragma once
#include "common.h"
#include "error_macros.h"

#include <utils/utils.h>

#include "ft2build.h"
#include FT_FREETYPE_H

#include <engine/Point.h>
#include <engine/buffers/buffers.h>
#include <engine/mvp/MVP.h>
#include <engine/shaders/Shaders.h>
#include <engine/textures/Texture.h>

namespace GEngine {
namespace Text {

#define CHARS_LIST std::map<GLchar, Character>

struct Character {
	GEngine::Texture* _textureID;  // Character texture
	glm::ivec2 _size;			   // Size of the glyph
	glm::ivec2 _bearing;		   // Offset from baseline to left/top of glyph
	GLuint _advance;			   // Offset to advance to next glyph
};

static std::map<std::string, FT_Face> t_Fonts;
static std::map<std::string, CHARS_LIST> t_Characters;

static GEngine::Shader* t_Shaders = nullptr;
static GEngine::VBO* t_VBO = nullptr;
static GEngine::VAO* t_VAO = nullptr;

static FT_Library ft;

class TextRenderer {
   public:
	// Initializes freetype2 library.
	// Loads shaders and sets up buffers.
	static void Init(void);
	static void DeInit(void);

	static void LoadFont(std::string fontname, std::string fontpath);
	static void UnLoadFont(std::string fontname);
	static void UnLoadAllFonts(void);

	static void LoadCharacters(std::string fontname);
	static void UnLoadCharacters(std::string fontname);
	static void UnLoadAllCharacters(void);

	static void RenderText(std::string text, std::string fontname,
						   GLfloat scale, GEngine::Point location,
						   glm::vec3 color, GEngine::MVP* mvp);

   private:
};

}  // namespace Text
}  // namespace GEngine

#endif