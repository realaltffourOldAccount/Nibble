#include "PostEffect.h"

namespace GEngine {
    namespace Effects {
        namespace Post {
            PostEffect::PostEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination) {
                this->mSource = source;
                this->mDestination = destination;
            }

            PostEffect::PostEffect(GEngine::FrameBuffer* source, GEngine::FrameBuffer* destination, int id) {
                this->mSource = source;
                this->mDestination = destination; 
                this->mID = id;
            }
            PostEffect::~PostEffect(void) {}

            void PostEffect::setTicks(int tick) { this->mTicks = tick; }
            void PostEffect::setStrength(float str) { this->mStrength = str; }
            void PostEffect::setID(int id) { this->mID = id; }

            int PostEffect::GetTicks(void) { return this->mTicks; }
            int PostEffect::GetCurrentTick(void) { return this->mCurrentTick; }
            float PostEffect::GetStrength(void) { return this->mStrength; }
            int PostEffect::GetID(void) { return this->mID; }

        }  // namespace Post
    }  // namespace Effects
}  // namespace GEngine
