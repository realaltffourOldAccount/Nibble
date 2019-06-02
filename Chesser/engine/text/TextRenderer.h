/**
 * @file TextRenderer.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains the definition of the text renderer.
 * @version 0.1
 * @date 2019-05-31
 *
 */
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

/**
 * @brief Represents the characters list.
 *
 */
#define CHARS_LIST std::map<GLchar, Character>

/**
 * @brief Represents a character.
 *
 */
struct Character {
	GEngine::Texture* _textureID;  // Character texture
	glm::ivec2 _size;			   // Size of the glyph
	glm::ivec2 _bearing;		   // Offset from baseline to left/top of glyph
	GLuint _advance;			   // Offset to advance to next glyph
};

/**
 * @brief Holds the fonts cache.
 *
 */
static std::map<std::string, FT_Face> t_Fonts;

/**
 * @brief Holds the characters cache.
 *
 */
static std::map<std::string, CHARS_LIST> t_Characters;

/**
 * @brief Special Shaders for text rendering.
 *
 */
static GEngine::Shader* t_Shaders = nullptr;

/**
 * @brief Vertex Buffer Object contains the characters vertices information.
 *
 */
static GEngine::VBO* t_VBO = nullptr;

/**
 * @brief Vertex Array Buffer Object contains the characters vertices
 * specifications.
 *
 */
static GEngine::VAO* t_VAO = nullptr;

/**
 * @brief Holds the freetype library.
 *
 */
static FT_Library ft;

/**
 * @brief The Text Renderer Class.
 *
 */
class TextRenderer {
   public:
	/**
	 * @brief  Initializes freetype2 library, loads shaders and sets up buffers
	 *
	 */
	static void Init(void);
	/**
	 * @brief Deinitializes freetype2 library, unloads shaders and buffers.
	 *
	 */
	static void DeInit(void);

	/**
	 * @brief Loads a font to the cache.
	 *
	 * @param fontname	The font name to be refrenced later.
	 * @param fontpath	The file path to be read from.
	 */
	static void LoadFont(std::string fontname, std::string fontpath);
	/**
	 * @brief Unloads a font from the cache.
	 *
	 * @param fontname	The font name to be deleted from the cache.
	 */
	static void UnLoadFont(std::string fontname);
	/**
	 * @brief Unloads all fonts from the cache.
	 *
	 */
	static void UnLoadAllFonts(void);

	/**
	 * @brief Loads characters to the cache from the font cache.
	 *
	 * @param fontname The font name to load the characters from.
	 */
	static void LoadCharacters(std::string fontname);
	/**
	 * @brief Unloads characters from the cache of a particular font.
	 *
	 * @param fontname The font name.
	 */
	static void UnLoadCharacters(std::string fontname);
	/**
	 * @brief Unloads all characters from the cache.
	 *
	 */
	static void UnLoadAllCharacters(void);

	/**
	 * @brief Renders text to the text.
	 *
	 * @param text		The text to be rendered.
	 * @param fontname	The font to be used.
	 * @param scale		The scale of the text.
	 * @param location	The location on the screen of the text.
	 * @param color		The color of the text.
	 * @param mvp		The MVP to be used.
	 */
	static void RenderText(std::string text, std::string fontname,
						   GLfloat scale, GEngine::Point location,
						   glm::vec3 color, GEngine::MVP* mvp);

   private:
};

}  // namespace Text
}  // namespace GEngine

#endif