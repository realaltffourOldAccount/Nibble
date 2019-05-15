#ifndef VBO_H
#define VBO_H
#pragma once

#include "BufferObject.h"
#include "common.h"

namespace GEngine {
class VBO {
  public:
    VBO(GLint usage, size_t size = 0, void* data = nullptr);
    ~VBO(void);

    void bind(void);
    void unbind(void);

    void destroy(void);

  private:
    GEngine::BufferObject* _buffer = nullptr;
};
} // namespace GEngine

#endif