#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include "common.h"
#include "error_macros.h"

namespace GEngine {
static vector<GLuint>* g_tex_slots =
	new vector<GLuint>(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, -1);
static GLuint g_tex_slot_cnt = 0;

static inline int FindEmptyTexSlot() {
	for (int i = 0; i < g_tex_slots->size(); i++)
		if ((*g_tex_slots)[i] == -1) return i;
	return -1;
}

static inline void AddTexSlot(int index) {
	(*g_tex_slots)[index] = g_tex_slot_cnt++;
}

static inline void RemoveTexSlot(int index) {
	(*g_tex_slots)[index] = -1;
	g_tex_slot_cnt--;
}

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

	const GLvoid* _data;

	TextureProps(GLint wrapS, GLint wrapT, GLint min_filter, GLint mag_filter,
				 GLint width, GLint height, GLint border, GLint level,
				 GLint internal_format, GLint buffer_format, GLenum type,
				 const GLvoid* data)
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
		  _data(data) {}
};

class Texture {
   public:
	Texture(std::string file, GLuint tex_id = 0);
	Texture(TextureProps prop);
	~Texture(void);

	GLuint getID(void);

	void bind(int index = -1);
	void unbind(void);

	int getImgWidth(void);
	int getImgHieght(void);
	int getImgCompNum(void);

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