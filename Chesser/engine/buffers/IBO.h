#ifndef IBO_H
#define IBO_H
#pragma once

#include "univ_includes.h"
#include "BufferObject.h"

namespace GEngine {
    class IBO {
        public:
        IBO(GLint usage, size_t size = 0, void* data = nullptr);
        ~IBO(void);

        void bind(void);
        void unbind(void);

        void destroy(void);

        private:
        GEngine::BufferObject* _buffer = nullptr;
    };
}

#endif