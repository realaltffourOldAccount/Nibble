#include "VAO.h"

GEngine::VAO::VAO(GEngine::VBO* vbo, vector<ShaderAttrib*> attribs) {
    _attribs = attribs;
    //#ifndef __ANDROID__
    this->_vbo = vbo;
    GLCall(glGenVertexArrays(1, &this->_vaoID));
    GLCall(glBindVertexArray(this->_vaoID));
    this->_vbo->bind();
    for (int i = 0; i < attribs.size(); i++)
        this->enableAttrib(attribs[i]);
    GLCall(glBindVertexArray(0));
    //#endif
}

GEngine::VAO::~VAO(void) { this->destroy(); }

void GEngine::VAO::bind(void) {
    //#ifdef __ANDROID__
    //    for (int i = 0; i < this->_attribs.size(); i++)
    //        this->enableAttrib(this->_attribs[i]);
    //#else
    GLCall(glBindVertexArray(this->_vaoID));
    //#endif
}

void GEngine::VAO::unbind(void) { GLCall(glBindVertexArray(0)); }

void GEngine::VAO::destroy(void) {
    //#ifndef __ANDROID__
    delete this->_vbo;
    GLCall(glDeleteVertexArrays(1, &this->_vaoID));
    //#endif
}

void GEngine::VAO::enableAttrib(ShaderAttrib* attrib) {
    GLCall(glEnableVertexAttribArray(attrib->_index));
    GLCall(glVertexAttribPointer(attrib->_index, attrib->_size, attrib->_type,
                                 attrib->_isNorm, attrib->_stride,
                                 attrib->_offset));
}