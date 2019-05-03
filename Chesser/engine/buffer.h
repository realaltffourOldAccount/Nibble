#ifndef BUFFER_H
#define BUFFER_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <glm/glm.hpp>

class BufferObject {
public:
    BufferObject(int targ, int use, void* dat, 
        size_t size) {
        glGenBuffers(1, &id);
        glBindBuffer(targ, id);
        glBufferData(targ, size, dat, use);
        
        target = targ;
        usage = use;
        data = dat;
        bf_size = size;
    }

    void bind() {
      glBindBuffer(target, id);
    }

    void unbind() {
      glBindBuffer(target,0);
    }

    void clean() {
        glDeleteBuffers(1, &id);
        data = nullptr;
        bf_size = 0;
        usage = -1;
    };

    unsigned int id = -1;
    int target;
    void* data = nullptr;
    size_t bf_size;
    int usage;
};

#endif
