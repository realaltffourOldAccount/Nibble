#ifndef VBO_H
#define VBO_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "univ_includes.h"
#include "buffer.h"

namespace VBOs {

static std::map<std::string, BufferObject*> vbo;

static void createVBO(std::string name, int usage, size_t size = 0,
                      void* data = nullptr) {
    BufferObject* new_vbo =
        new BufferObject(GL_ARRAY_BUFFER, usage, data, size);
    vbo[name] = new_vbo;
}

static void clean() {
    std::map<std::string, BufferObject*>::iterator it;
    for (it = vbo.begin(); it != vbo.end(); it++) it->second->clean();

    vbo.clear();
}

}  // namespace VBOs

#endif