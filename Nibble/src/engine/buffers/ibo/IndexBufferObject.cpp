#include "IndexBufferObject.h"

GEngine::IBO::IBO(GLint usage, size_t size, void* data) {
    this->_buffer =
        new GEngine::BufferObject(GL_ELEMENT_ARRAY_BUFFER, usage, data, size);
}

GEngine::IBO::~IBO(void) { this->destroy(); }

void GEngine::IBO::bind(void) { this->_buffer->bind(); }

void GEngine::IBO::unbind(void) { this->_buffer->unbind(); }

void GEngine::IBO::destroy(void) {
    this->_buffer->destroy();
    delete this->_buffer;
}
