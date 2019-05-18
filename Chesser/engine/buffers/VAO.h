#ifndef VAO_H
#define VAO_H
#pragma once

#include "BufferObject.h"
#include "VBO.h"
#include "common.h"
#include "error_macros.h"

namespace GEngine {
struct ShaderAttrib {
    GLint _index;
    GLsizei _size;
    GLsizei _stride;
    void* _offset;
    GLenum _type;
    GLboolean _isNorm = false;
    GLboolean _isEnable = true;
};

class VAO {
  public:
    VAO(GEngine::VBO* vbo, vector<ShaderAttrib*> attribs);
    ~VAO(void);

    void bind(void);
    void unbind(void);

    void destroy(void);

  private:
    void enableAttrib(ShaderAttrib* attrib);

    GEngine::VBO* _vbo = nullptr;
    GLuint _vaoID;
    vector<ShaderAttrib*> _attribs;
};
} // namespace GEngine

#endif