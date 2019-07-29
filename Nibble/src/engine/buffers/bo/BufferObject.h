/**
 * @file BufferObject.h
 * @author Ayham Mamoun (ayhamaboualfald@gmail.com)
 * @brief Contains an abstract definition of an OpenGL buffer.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef BUFFER_OBJ_H
#define BUFFER_OBJ_H
#pragma once

#include "common.h"
#include "error_macros.h"

namespace GEngine {
    /**
     * @brief An abstract definition of an OpenGL buffer.
     *
     */
    class BufferObject {
        public:
            /**
             * @brief Construct a new Buffer Object object.
             *
             * @param target 	The OpenGL buffer target.
             * @param usage	The usage of the buffer target.
             * @param dat		The data of the buffer.
             * @param size		The size of the data.
             */
            BufferObject(int target, int usage, void* dat, size_t size);
            /**
             * @brief Destroy the Buffer Object object.
             *
             */
            ~BufferObject(void);

            /**
             * @brief Bind the Buffer Object instance to be used.
             *
             */
            void bind(void);
            /**
             * @brief Unbinds the Buffer Object instance.
             *
             */
            void unbind(void);

            /**
             * @brief Destroy the Buffer Object object manually.
             *
             */
            void destroy(void);

        private:
            GLuint _bId = -1;
            GLint _target;
            void* _data = nullptr;
            size_t _bf_size;
            int _usage;
    };
};  // namespace GEngine

#endif
