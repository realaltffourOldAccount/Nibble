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
            class BlurEffect : PostEffect {
                public:
                    BlurEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination);
                    BlurEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination, int strength);
                    ~BlurEffect(void);

                    void render(void) override;
                    void tick(void) override;
                    void destroy(void) override;

                private:
                    void initShaders(void);
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
