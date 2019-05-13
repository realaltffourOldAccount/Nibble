#include "VAO.h"

GEngine::VAO::VAO(GEngine::VBO* vbo, vector<ShaderAttrib*> attribs) {
    this->_vbo = vbo;
    GLCall(glGenVertexArrays(1, &this->_vaoID));
    GLCall(glBindVertexArray(this->_vaoID));
    this->_vbo->bind();
    for (int i = 0; i < attribs.size(); i++)
        this->enableAttrib(attribs[i]);
    GLCall(glBindVertexArray(0));
}

GEngine::VAO::~VAO(void) { this->destroy(); }

void GEngine::VAO::bind(void) { GLCall(glBindVertexArray(this->_vaoID)); }

void GEngine::VAO::unbind(void) { GLCall(glBindVertexArray(0)); }

void GEngine::VAO::destroy(void) {
    delete this->_vbo;
    GLCall(glDeleteVertexArrays(1, &this->_vaoID));
}

void GEngine::VAO::enableAttrib(ShaderAttrib* attrib) {
    GLCall(glEnableVertexAttribArray(attrib->_index));
    GLCall(glVertexAttribPointer(attrib->_index, attrib->_size, attrib->_type,
                                 attrib->_isNorm, attrib->_stride,
                                 attrib->_offset));
}