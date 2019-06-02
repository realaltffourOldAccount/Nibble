/**
 * @file Texture.h
 * @author Ayham Mamoun (ayhamaboulfadl@gmail.com)
 * @brief Contains an abstract definition of a texture.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include "common.h"
#include "error_macros.h"

namespace GEngine {
/**
 * @brief Contains references to tex slots currently bound.
 *
 */
static vector<GLuint>* g_tex_slots =
	new vector<GLuint>(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, -1);
/**
 * @brief Contains the count of texture slots currently bound.
 *
 */
static GLuint g_tex_slot_cnt = 0;

/**
 * @brief Finds an empty texture bind slot index.
 *
 * @return int The slot index.
 */
static inline int FindEmptyTexSlot() {
	for (int i = 0; i < g_tex_slots->size(); i++)
		if ((*g_tex_slots)[i] == -1) return i;
	return -1;
}

/**
 * @brief Fills a texture bind slot with the texture nu,ber.
 *
 * @param index The texture bind slot index.
 */
static inline void AddTexSlot(int index) {
	if (index >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) {
		THROW_ERROR("Texture Slot index not supported.",
					Log::GenLogID(__LINE__, __FILE__, "Texture", __func__));
	}
	(*g_tex_slots)[index] = ++g_tex_slot_cnt;
}

/**
 * @brief Clears a texture bind slot with -1.
 *
 * @param index	The texture bind slot index.
 */
static inline void RemoveTexSlot(int index) {
	if (index < 0) {
		THROW_ERROR("Texture Slot index can't be below 0.",
					Log::GenLogID(__LINE__, __FILE__, "Texture", __func__));
	}
	(*g_tex_slots)[index] = -1;
	g_tex_slot_cnt--;
}

/**
 * @brief A representation of texture properietes.
 *
 */
struct TextureProps {
	GLint _wrapS;
	GLint _wrapT;
	GLint _min_filter;
	GLint _mag_filter;

	GLint _width;
	GLint _height;

	GLint _border;

	GLint _level;
	GLint _internalFormat;
	GLenum _type;
	GLint _bufferFormat;

	bool _gen_mipmap = false;

	const GLvoid* _data;
	TextureProps() {}
	TextureProps(GLint wrapS, GLint wrapT, GLint min_filter, GLint mag_filter,
				 GLint width, GLint height, GLint border, GLint level,
				 GLint internal_format, GLint buffer_format, GLenum type,
				 const GLvoid* data, bool gen_mipmap)
		: _wrapS(wrapS),
		  _wrapT(wrapT),
		  _min_filter(min_filter),
		  _mag_filter(mag_filter),
		  _width(width),
		  _height(height),
		  _border(border),
		  _level(level),
		  _internalFormat(internal_format),
		  _bufferFormat(buffer_format),
		  _type(type),
		  _data(data),
		  _gen_mipmap(gen_mipmap) {}
};

/**
 * @brief An abstract definition of a texture object.
 *
 */
class Texture {
   public:
	/**
	 * @brief Construct a new Texture object
	 *
	 * @param file	The texture file path to be read.
	 */
	Texture(std::string file);
	/**
	 * @brief Construct a new Texture object
	 *
	 * @param prop 	The texture properties.
	 */
	Texture(TextureProps prop);
	/**
	 * @brief Destroy the Texture object.
	 *
	 */
	~Texture(void);

	/**
	 * @brief Binds the texture to be used.
	 *
	 * @param index	The index for the texture to be bound to, default finds an
	 * empty slot automatically.
	 */
	void bind(int index = -1);
	/**
	 * @brief Unbinds the texture.
	 *
	 */
	void unbind(void);

	/**
	 * @brief Get the Image Width.
	 *
	 * @return int
	 */
	int getImgWidth(void);
	/**
	 * @brief Get the Image Height.
	 *
	 * @return int
	 */
	int getImgHeight(void);
	/**
	 * @brief Get the Image Component Number.
	 *
	 * @return int
	 */
	int getImgCompNum(void);

	/**
	 * @brief Destroyes the texture object.
	 *
	 */
	void destroy(void);

   private:
	GLuint _tex_id;
	int _imgWidth;
	int _imgHeight;
	int _imgComp;
	int _slot_bound = -1;
};
}  // namespace GEngine

#endif