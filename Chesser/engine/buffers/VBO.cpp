#include "VBO.h"

GEngine::VBO::VBO(GLint usage, size_t size, void* data) {
	this->_buffer =
		new GEngine::BufferObject(GL_ARRAY_BUFFER, usage, data, size);
}

GEngine::VBO::~VBO(void) { this->destroy(); }

void GEngine::VBO::bind(void) { this->_buffer->bind(); }

void GEngine::VBO::unbind(void) { this->_buffer->unbind(); }

void GEngine::VBO::destroy(void) { delete this->_buffer; }
