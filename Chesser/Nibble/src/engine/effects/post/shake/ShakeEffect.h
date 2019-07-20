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
            class ShakeEffect : PostEffect {
                public:
                    ShakeEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination);
                    ShakeEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination, int ticks, float strength);
                    ~ShakeEffect(void);

                    void render(void) override;
                    void tick(void) override;
                    void destroy(void) override;

                private:
                    void initShaders(void);
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
