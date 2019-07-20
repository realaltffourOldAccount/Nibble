#include "VertexArrayObject.h"

GEngine::VAO::VAO(GEngine::VBO* vbo, vector<ShaderAttrib*> attribs) {
    this->_attribs = attribs;
    this->_vbo = vbo;
    if (g_config->_corevertexArraySupport || g_config->_ARBvertexArraySupport) {
        GLCall(glGenVertexArrays(1, &this->_vaoID));
        GLCall(glBindVertexArray(this->_vaoID));
        this->_vbo->bind();
        for (int i = 0; i < attribs.size(); i++) this->enableAttrib(attribs[i]);
        GLCall(glBindVertexArray(0));
        this->_vbo->unbind();
    } else if (g_config->_EXTvertexArraySupport) {
        GLCall(glGenVertexArrays(1, &this->_vaoID));
        GLCall(glBindVertexArray(this->_vaoID));
        this->_vbo->bind();
        for (int i = 0; i < attribs.size(); i++) this->enableAttrib(attribs[i]);
        GLCall(glBindVertexArray(0));
        this->_vbo->unbind();
    }
}

GEngine::VAO::VAO(vector<ShaderAttrib*> attribs) {
    this->_attribs = attribs;
    if (g_config->_corevertexArraySupport || g_config->_ARBvertexArraySupport) {
        GLCall(glGenVertexArrays(1, &this->_vaoID));
        GLCall(glBindVertexArray(this->_vaoID));
        for (int i = 0; i < attribs.size(); i++) this->enableAttrib(attribs[i]);
        GLCall(glBindVertexArray(0));
    } else if (g_config->_EXTvertexArraySupport) {
        GLCall(glGenVertexArrays(1, &this->_vaoID));
        GLCall(glBindVertexArray(this->_vaoID));
        for (int i = 0; i < attribs.size(); i++) this->enableAttrib(attribs[i]);
        GLCall(glBindVertexArray(0));
    }
}

GEngine::VAO::~VAO(void) { this->destroy(); }

void GEngine::VAO::bind(void) {
    if (g_config->_corevertexArraySupport || g_config->_ARBvertexArraySupport) {
        GLCall(glBindVertexArray(this->_vaoID));
    } else if (g_config->_EXTvertexArraySupport) {
        GLCall(glBindVertexArray(this->_vaoID));
    } else {
        for (int i = 0; i < this->_attribs.size(); i++) 
            this->enableAttrib(this->_attribs[i]);
    }
}

void GEngine::VAO::unbind(void) {
    if (g_config->_corevertexArraySupport || g_config->_ARBvertexArraySupport) {
        GLCall(glBindVertexArray(0));
    } else if (g_config->_EXTvertexArraySupport) {
        GLCall(glBindVertexArray(0));
    }
}

void GEngine::VAO::destroy(void) {
    if (g_config->_corevertexArraySupport || g_config->_ARBvertexArraySupport) {
        delete this->_vbo;
        GLCall(glDeleteVertexArrays(1, &this->_vaoID));
    } else if (g_config->_EXTvertexArraySupport) {
        delete this->_vbo;
        GLCall(glDeleteVertexArrays(1, &this->_vaoID));
    }
}

void GEngine::VAO::enableAttrib(ShaderAttrib* attrib) {
    if (attrib->_isEnable) GLCall(glEnableVertexAttribArray(attrib->_index));
    GLCall(glVertexAttribPointer(attrib->_index, attrib->_size, attrib->_type,
                attrib->_isNorm, attrib->_stride,
                attrib->_offset));
}
