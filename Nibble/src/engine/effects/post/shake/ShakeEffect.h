/**
 * @file ShakeEffect.h 
 * @auther Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @version 0.1
 * @date 2019-06-26
 *
 */

#ifndef EFFECTS_POST_SHAKE_H
#define EFFECTS_POST_BLUR_H

#include "common.h"

#include <engine/buffers/fb/FrameBuffer.h>
#include <engine/effects/post/PostEffect.h>
#include <engine/shaders/Shaders.h>
#include <engine/textures/Texture.h>
#include <engine/buffers/buffers.h>

namespace GEngine {
    namespace Effects {
        namespace Post {
            extern GEngine::Shader* ep_shake_shaders;
            /**
             * @breif Represents the ShakeEffect Object.
             */
            class ShakeEffect : PostEffect {
                public:
                    /**
                     * @breif Creates the ShakeEffect object.
                     *
                     * @param source      The Source of the shake effect.
                     * @param destination The DEstination of the shake effect.
                     */
                    ShakeEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination);
                    /**
                     * @breif Creates the ShakeEffect object.
                     *
                     * @param source      The Source of the shake effect.
                     * @param destination The Destination of the shake effect.
                     * @param ticks       The Duration of the Shake effect.
                     * @param strength    The Strength of the SHakeEffect.
                     */                   
                    ShakeEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination, int ticks, float strength);
                    /**
                     * @breif Destroys the ShakeEffect Object.
                     */
                    ~ShakeEffect(void);

                    /**
                     * @brief Renders the ShakeEffect to the Destination
                     */
                    void render(void) override;
                    /**
                     * @breif Updates the ShakeEffect (Used to offset the scene).
                     */
                    void tick(void) override;
                    /**
                     * @breif Destroys the ShakeEffect Object.
                     */
                    void destroy(void) override;

                private:
                    /**
                     * @breif Initializes the shaders.
                     */
                    void initShaders(void);
                    /**
                     * @breif Initialies the Buffers.
                     */
                    void initBuffers(void);

                    float mStrength = 0.0;

                    GEngine::VBO* mVBO = nullptr;
                    GEngine::IBO* mIBO = nullptr;
                    GEngine::VAO* mVAO = nullptr;

                    GLfloat* mBufferData = nullptr;
                    GLubyte* mIndicesData = nullptr;

                    vector<GEngine::ShaderAttrib*> mShaderAttribs;
            };
        }
    }
}
#endif
