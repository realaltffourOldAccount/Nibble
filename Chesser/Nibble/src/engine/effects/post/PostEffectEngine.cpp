#include "PostEffectEngine.h"

namespace GEngine {
    namespace Effects {
        namespace Post {
            PostEffectEngine::PostEffectEngine(void) {}
            PostEffectEngine::PostEffectEngine(vector<PostEffect*> effects) {
                this->mEffects = effects;
            }

            PostEffectEngine::~PostEffectEngine(void) {
                this->destroy();
            }

            void PostEffectEngine::AddEffect(PostEffect* effect) {
                this->mEffects.push_back(effect);
            }
            void PostEffectEngine::RemoveEffect(int index) {
                this->mEffects.erase(this->mEffects.begin()+index);
            }

            void PostEffectEngine::render(void) {
                for (int i = 0; i < this->mEffects.size(); i++)
                    if (this->mEffects[i])
                        this->mEffects[i]->render();
            }
            void PostEffectEngine::tick(void) {
                for (int i = 0; i < this->mEffects.size(); i++)
                    if (this->mEffects[i])
                        this->mEffects[i]->tick();
            }
            void PostEffectEngine::destroy(void) {
                for (int i = 0; i < this->mEffects.size(); i++)
                    if (this->mEffects[i])
                        this->mEffects[i]->destroy();
            }

        }
    }
}
