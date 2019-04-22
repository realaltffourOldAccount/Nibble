#ifndef IBO_H
#define IBO_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "univ_includes.h"

#include "buffer.h"

namespace IBOs {
static std::map<std::string, BufferObject*> ibo;

static void createIBO(std::string name, int usage, size_t size = 0,
                      void* data = nullptr) {
    BufferObject* new_ibo =
        new BufferObject(GL_ELEMENT_ARRAY_BUFFER, usage, data, size);
    ibo[name] = new_ibo;
}

static void clean() {
    std::map<std::string, BufferObject*>::iterator it;
    for (it = ibo.begin(); it != ibo.end(); it++) it->second->clean();
    ibo.clear();
}

};  // namespace IBOs

#endif