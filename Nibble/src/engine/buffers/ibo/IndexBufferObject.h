/**
 * @file IndexBufferObject.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains an abstract definition of an OpenGL Indices Buffer.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef IBO_H
#define IBO_H
#pragma once

#include "../bo/BufferObject.h"
#include "common.h"

namespace GEngine {
    /**
     * @brief An abstract definition of an OpenGL Indices Buffer.
     *
     */
    class IBO {
        public:
            /**
             * @brief Construct a new IBO object.
             *
             * @param usage 	The usage of the buffer.
             * @param size		The size of the buffer data.
             * @param data		The data of the buffer.
             */
            IBO(GLint usage, size_t size = 0, void* data = nullptr);
            /**
             * @brief Destroy the IBO object.
             *
             */
            ~IBO(void);

            /**
             * @brief Binds the Indices Buffer Object instance to be used.
             *
             */
            void bind(void);
            /**
             * @brief Unbinds the Indices Buffer Object instance.
             *
             */
            void unbind(void);

            /**
             * @brief Destroys the Indices Buffer Object Instance.
             *
             */
            void destroy(void);

        private:
            GEngine::BufferObject* _buffer = nullptr;
    };
}  // namespace GEngine

#endif
