#ifndef VAO_H
#define VAO_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "univ_includes.h"
#include "buffer.h"

namespace VAOs {

struct ShaderAttrib() {
    int index;
    GLsizei size;
    GLsizei stride;
    void* offset;
    GLenum type;
    bool isNorm = false;
    bool isEnable = true;
}

static std::map<std::string, VAO*> vao;

static void createVAO(std::string name, BufferObject* vbo);

class VAO {
public:
    VAO(BufferObject* vbo, vector<ShaderAttrib*> attribs) {
        glGenVertexArrays(1, &ID); 
        glBindVertexArray(ID);
        vbo->bind();
        for (int i = 0; i < attribs.size(); i++)
          this->enableAttrib(attribs[i]);
        glBindVertexArray(ID);
    }

    void bind() {
      glBindVertexArray(ID);
    }
    
    void unbind() {
      glBindVertexArray(0);
    }

private:
    void enableAttrib(ShaderAttrib* attrib) {
        glBindVertexArray(ID);
        glEnableVertexAttribArray(attrib->index);
        glVertexAttribPointer(attrib->index, attrib->size, 
            attrib->type, 
            attrib->isNorm, attrib->stride, attrib->offset);
        glBindVertexArray(0);
    }

private:
    GLuint ID;
    BufferObject* _vbo;
    BufferObject* _ibo;
    vector<ShaderAttrib*> _attribs;
};

}  // namespace VAOs

#endif
