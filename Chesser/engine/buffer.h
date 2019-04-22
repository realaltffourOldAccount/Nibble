#ifndef BUFFER_H
#define BUFFER_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <glm/glm.hpp>

class BufferObject {
public:
    BufferObject(int target, int usage, void* data, 
        size_t size) {
        glGenBuffers(1, &id);
        glBindBuffer(target, id);
        glBufferData(target, size, data, usage);
    }

    void bind() {
      glBindBuffer(id);
    }

    void unbind() {
      glBindBubber(0);
    }

    void clean() {
        glDeleteBuffers(1, &id);
        delete data;
        bf_size = 0;
        usage = -1;
    };

    unsigned int id = -1;
    void* data = nullptr;
    size_t bf_size;
    int usage;
};

#endif
