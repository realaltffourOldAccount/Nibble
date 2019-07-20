#include "Input.h"

namespace GEngine {
    Input::Input(void) {}
    Input::~Input(void) {}

    void Input::Init() {
        for (int i = 0; i < API_INPUT_KEY_COUNT; i++) {
            this->mKeys[i] = false;
        }
        for (int i = 0; i < API_INPUT_MOUSE_BUTTON_COUNT; i++) {
            this->mMouseKeys[i] = false;
        }
        for (int i = 0; i < API_INPUT_ANDROID_TOUCH_COUNT; i++) {
            this->mTouchState[i] = false;
        }

        this->mMouseX = 0;
        this->mMouseY = 0;

        this->mTouchX = 0;
        this->mTouchY = 0;

    }  // namespace GEngine

    void Input::RegisterKey(int code) {
        if (API_INPUT_KEY_FIRST <= code <= API_INPUT_KEY_LAST)
            this->mKeys[code] = true;
    }
    void Input::UnRegisterKey(int code) {
        if (API_INPUT_KEY_FIRST <= code <= API_INPUT_KEY_LAST)
            this->mKeys[code] = false;
    }

    void Input::RegisterMouseKey(int code) {
        if (API_INPUT_MOUSE_BUTTON_FIRST <= code <= API_INPUT_MOUSE_BUTTON_LAST)
            this->mMouseKeys[code] = true;
    }
    void Input::UnRegisterMouseKey(int code) {
        if (API_INPUT_MOUSE_BUTTON_FIRST <= code <= API_INPUT_MOUSE_BUTTON_LAST)
            this->mMouseKeys[code] = false;
    }

    void Input::RegisterMousePosition(int x, int y) {
        this->mMouseX = x;
        this->mMouseY = y;
    }

    void Input::RegisterTouchPosition(int x, int y) {
        this->mTouchX = x;
        this->mTouchY = y;
    }

    void Input::RegisterTouchState(int state) {
        if (API_INPUT_ANDROID_TOUCH_FIRST <= state <=
                API_INPUT_ANDROID_TOUCH_LAST) {
            for (int i = 0; i < API_INPUT_ANDROID_TOUCH_COUNT; i++) {
                this->mTouchState[i] = false;
            }
            this->mTouchState[state] = true;
        }
    }

    bool Input::IsMouseKeyPressed(int code) {
        if (API_INPUT_MOUSE_BUTTON_FIRST <= code <= API_INPUT_MOUSE_BUTTON_LAST)
            return this->mMouseKeys[code];
    }
    bool Input::IsMouseKeyReleased(int code) {
        if (API_INPUT_MOUSE_BUTTON_FIRST <= code <= API_INPUT_MOUSE_BUTTON_LAST)
            return !this->mMouseKeys[code];
    }

    bool Input::IsKeyPressed(int code) {
        if (API_INPUT_KEY_FIRST <= code <= API_INPUT_KEY_LAST)
            return this->mKeys[code];
    }
    bool Input::IsKeyReleased(int code) {
        if (API_INPUT_KEY_FIRST <= code <= API_INPUT_KEY_LAST)
            return !this->mKeys[code];
    }

    bool Input::IsTouchState(int state) {
        if (API_INPUT_ANDROID_TOUCH_FIRST <= state <= API_INPUT_ANDROID_TOUCH_LAST)
            return this->mTouchState[state];
    }

    void Input::ResetState() { this->Init(); }
}  // namespace GEngine
