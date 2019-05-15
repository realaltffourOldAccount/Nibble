#ifndef SHADERS_H
#define SHADERS_H
#pragma once

// Shader's standard for uniform attributes
#define SHADER_ATTRIB_POS 0
#define SHADER_ATTRIB_COLOR 1
#define SHADER_ATTRIB_TEXCOORD 2 // if needed

#include "common.h"
#include "error_macros.h"

namespace GEngine {
class Shader {
  public:
    Shader(const std::string vsfile, const std::string fsfile);
    ~Shader(void);

    void bind(void);
    void unbind(void);

    void destroy(void);

    int getProgId(void);

  private:
    GLuint _prog_id;
};
} // namespace GEngine

#endif