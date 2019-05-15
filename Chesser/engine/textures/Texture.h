#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include "common.h"
#include "error_macros.h"

namespace GEngine {
static GLuint last_tex_id = 0;
class Texture {
  public:
    Texture(std::string file, GLuint tex_id = 0);
    ~Texture(void);

    GLuint getID(void);

    void bind(int index);
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
};
} // namespace GEngine

#endif