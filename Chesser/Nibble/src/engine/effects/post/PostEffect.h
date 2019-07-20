/**
 * @file PostEffect.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains the definition of a post effect.
 * @version 0.1
 * @date 2019-06-26
 *
 */

#include "common.h"

#include <engine/textures/Texture.h>
#include <engine/buffers/fb/FrameBuffer.h>

namespace GEngine {
    namespace Effects {
        namespace Post {
            enum PostEffectID {
                Blur = 0,
                Shake,
            };
            class PostEffect {
                public:
                    PostEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination);
                    PostEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination, int id);
                    ~PostEffect(void);

                    virtual void render(void) = 0;
                    virtual void tick(void) = 0;
                    virtual void destroy(void) = 0;

                    void setTicks(int);
                    void setStrength(float);
                    void setID(int);

                    int GetTicks(void);
                    int GetCurrentTick(void);
                    float GetStrength(void);
                    int GetID(void);

                protected:
                    int mID;
                    unsigned int mText;
                    GEngine::FrameBuffer* mSource = nullptr;
                    GEngine::FrameBuffer* mDestination = nullptr;

                    int mTicks = 0;
                    int mCurrentTick = 0;
                    float mStrength = 0.0f;
            };
        }  // namespace Post
    }  // namespace Effects
}  // namespace GEngine
