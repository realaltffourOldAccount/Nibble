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
            /**
             * @brief Represents A PostEffect.
             */
            class PostEffect {
                public:
                    /**
                     * @brief Creates a PostEffect Object.
                     *
                     * @param source      The source of the effect.
                     * @param destination The destination of the effect.
                     */
                    PostEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination);
                    /**
                     * @brief Creates a PostEffect Object.
                     *
                     * @param soruce      The source of the effect.
                     * @param destination The destination of the effect.
                     * @param id          The ID of the effect. 
                     */
                    PostEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination, int id);
                    /**
                     * @brief Destroyes the PostEffect Object.
                     */
                    ~PostEffect(void);

                    /**
                     * @brief Renders the effect.
                     */
                    virtual void render(void) = 0;
                    /**
                     * @breif Update the effect.
                     */
                    virtual void tick(void) = 0;
                    /**
                     * @breif Destroys the effect object.
                     */
                    virtual void destroy(void) = 0;

                    /**
                     * @breif Sets the Duration of the effect in Update Ticks.
                     */
                    void setTicks(int);
                    /**
                     * @breif Sets the Strength of the effect.
                     */
                    void setStrength(float);
                    /**
                     * @breif Sets the ID of the PostEffect.
                     */
                    void setID(int);

                    /**
                     * @breif Returns the Duration of the effect in Update TIcks.
                     *
                     * @returns The Ticks.
                     */
                    int GetTicks(void);
                    /**
                     * @breif Returns the duration of the effect to the current Tick.
                     *
                     * @returns The Current Tick.
                     */
                    int GetCurrentTick(void);
                    /**
                     * @breif The Strength of the effect.
                     *
                     * @returns The strength.
                     */
                    float GetStrength(void);

                    /**
                     * @breif The ID(Type) of the PostEffect Object.
                     */
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
