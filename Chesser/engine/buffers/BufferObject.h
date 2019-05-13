#ifndef BUFFER_OBJ_H
#define BUFFER_OBJ_H
#pragma once

#include "error_macros.h"
#include "univ_includes.h"

namespace GEngine {
class BufferObject {
  public:
    BufferObject(int target, int usage, void* dat, size_t size);
    ~BufferObject(void);

    void bind(void);
    void unbind(void);

    void destroy(void);

  private:
    GLuint _bId = -1;
    GLint _target;
    void* _data = nullptr;
    size_t _bf_size;
    int _usage;
};
}; // namespace GEngine

#endif