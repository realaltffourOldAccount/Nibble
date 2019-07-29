#include "BufferObject.h"

GEngine::BufferObject::BufferObject(int target, int usage, void* dat,
        size_t size) {
    GLCall(glGenBuffers(1, &this->_bId));
    GLCall(glBindBuffer(target, this->_bId));
    GLCall(glBufferData(target, size, dat, usage));
    GLCall(glBindBuffer(target, 0));

    this->_target = target;
    this->_data = dat;
    this->_bf_size = size;
    this->_usage = usage;
}

GEngine::BufferObject::~BufferObject(void) { this->destroy(); }

void GEngine::BufferObject::bind(void) {
    GLCall(glBindBuffer(this->_target, this->_bId));
}

void GEngine::BufferObject::unbind(void) {
    GLCall(glBindBuffer(this->_target, 0));
}

void GEngine::BufferObject::destroy(void) {
    GLCall(glDeleteBuffers(1, &this->_bId));
    this->_data = nullptr;
    this->_bf_size = -1;
    this->_usage = -1;
}
