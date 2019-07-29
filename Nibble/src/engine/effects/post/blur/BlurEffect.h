/**
 * @file BlurEffect.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains the definition of the blur effect.
 * @version 0.1
 * @date 2019-06-26
 *
 */

#ifndef EFFECTS_POST_BLUR_H
#define EFFECTS_POST_BLUR_H

#include "common.h"

#include <engine/buffers/fb/FrameBuffer.h>
#include <engine/effects/post/PostEffect.h>
#include <engine/shaders/Shaders.h>
#include <engine/textures/Texture.h>

namespace GEngine {
    namespace Effects {
        namespace Post {
            extern GEngine::Shader* ep_blur_shaders;
            /**
             * @brief Represents the BlurEffect.
             */
            class BlurEffect : PostEffect {
                public:
                    /**
                     * @brief Creates a blur Effect.
                     *
                     * @param source      The source of the effect.
                     * @param destination The destination of the effect.
                     */
                    BlurEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination);
                    /**
                     * @brief Creates a blur Effect.
                     *
                     * @param source      The source of the effect.
                     * @param destination The destination of the effect.
                     * @param strength    The strength of the blur effect.
                     */ 
                    BlurEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination, int strength);
                    /**
                     * @brief Destroys the BlurEffect Object.
                     */
                    ~BlurEffect(void);

                    /**
                     * @brief Renders the effect to the destination.
                     */
                    void render(void) override;
                    /**
                     * @brief Updates the effect (Not used).
                     */
                    void tick(void) override;
                    /**
                     * @brief Destroys the BlurEffect Object.
                     */
                    void destroy(void) override;

                private:
                    /**
                     * @brief Initializes Shaders.
                     */
                    void initShaders(void);
                    /**
                     * @brief Initializes Buffers.
                     */
                    void initBuffers(void);

                    float mStrength = 4.0f;
                    glm::mat3 mKernel = glm::mat3(1.0f);

                    GEngine::VBO* mVBO = nullptr;
                    GEngine::IBO* mIBO = nullptr;
                    GEngine::VAO* mVAO = nullptr;

                    GLfloat* mBufferData = nullptr;
                    GLubyte* mIndicesData = nullptr;

                    vector<GEngine::ShaderAttrib*> mShaderAttribs;
            };
        }  // namespace Post
    }  // namespace Effects
}  // namespace GEngine

#endif
