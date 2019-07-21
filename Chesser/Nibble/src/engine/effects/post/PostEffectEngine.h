/**
 * @file PostEffectEngine.h
 * @auther Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contians the definition of the post efffects engine.
 * @verson 0.1
 * @date 2019-Jun-21
 * 
 */

#ifndef EFFECTS_POST_ENGINE_H
#define EFFECTS_POST_ENGINE_H

#include "common.h"

#include "PostEffect.h"
#include "blur/BlurEffect.h"
#include "shake/ShakeEffect.h"

namespace GEngine {
    namespace Effects {
        namespace Post {
            /**
             * @breif The PostEffectEngine.
             */
            class PostEffectEngine {
                public:
                    /**
                     * @breif Constructs a PostEffectEngine Object.
                     */
                    PostEffectEngine(void);
                    /**
                     * @breif Constructs a PostEffectEngine Object.
                     *
                     * @param effects The array of effect to preset to. 
                     */
                    PostEffectEngine(vector<PostEffect*> effects);
                    /**
                     * @breif Destroys the PostEffectEngine Object.
                     */
                    ~PostEffectEngine(void);

                    /**
                     * @breif Adds an effect.
                     *
                     * @param effect The effect to be added.
                     */
                    void AddEffect(PostEffect* effect);
                    /**
                     * @breif Removes an effect.
                     *
                     * @param index The index of the effect to remove.
                     */
                    void RemoveEffect(int index);

                    /**
                     * @breif Renders the effect in order of addition.
                     */
                    void render(void);
                    /**
                     * @breif Updates the effect in order of addition.
                     */
                    void tick(void);
                    /**
                     * @breif Destroys the PostEffectEngine Object.
                     */
                    void destroy(void);

                private:
                    vector<PostEffect*> mEffects;
            };

        }
    }
}

#endif
