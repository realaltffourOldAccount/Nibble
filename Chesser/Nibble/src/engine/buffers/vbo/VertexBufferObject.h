/**
 * @file VertexBufferObject.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains an abstract definition of an OpenGL Vertex Buffer.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef VBO_H
#define VBO_H
#pragma once

#include "../bo/BufferObject.h"
#include "common.h"

namespace GEngine {
    /**
     * @brief An Abstract definition of an OpenGL Vertex Buffer Object.
     *
     */
    class VBO {
        public:
            /**
             * @brief Construct a new VBO object.
             *
             * @param usage	The usage of the Vertex Buffer Object.
             * @param size		The size of the Vertex Buffer Object's data.
             * @param data		The data of the Vertex Buffer Object.
             */
            VBO(GLint usage, size_t size = 0, void* data = nullptr);
            /**
             * @brief Destroy the VBO object.
             *
             */
            ~VBO(void);

            /**
             * @brief Binds the Vertex Array Buffer Object to be used.
             *
             */
            void bind(void);
            /**
             * @brief Unbinds the Vertex Array Buffer Object.
             *
             */
            void unbind(void);

            /**
             * @brief Destroy the VBO Object Manually.
             *
             */
            void destroy(void);

        private:
            GEngine::BufferObject* _buffer = nullptr;
    };
}  // namespace GEngine

#endif
