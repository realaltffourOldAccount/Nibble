/**
 * @file Input.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Defines the Input Class.
 * @version 0.1
 * @date 2019-06-11
 *
 */

#include "InputCodes.h"

namespace GEngine {
    /**
     * @brief The Input Handling Class.
     *
     */
    class Input {
        public:
            /**
             * @brief Construct a new Input object.
             *
             */
            Input(void);
            /**
             * @brief Destroy the Input object
             *
             */
            ~Input(void);

            /**
             * @brief Initializes the Input States.
             *
             */
            void Init(void);
            /**
             * @brief Sets a Key Code to true.
             *
             * @param code The Key Code to be set.
             */
            void RegisterKey(int code);
            /**
             * @brief Sets a Key Code to false.
             *
             * @param code The Key Code to be set.
             */
            void UnRegisterKey(int code);

            /**
             * @brief Sets a Mouse Key Code to true.
             *
             * @param code The Mouse Key Code to be set.
             */
            void RegisterMouseKey(int code);
            /**
             * @brief Sets a Mouse Key Code to false.
             *
             * @param code The Mouse Key Code to be set.
             */
            void UnRegisterMouseKey(int code);

            /**
             * @brief Sets the Mouse Position.
             *
             * @param x The Mouse Position.
             * @param y The Mouse Position.
             */
            void RegisterMousePosition(int x, int y);

            /**
             * @brief Sets the last touch position.
             *
             * @param x The Touch Position.
             * @param y The Touch Position.
             */
            void RegisterTouchPosition(int x, int y);

            /**
             * @brief Sets the state of the last touch.
             *
             * @param state	The state to set to.
             */
            void RegisterTouchState(int state);

            /**
             * @brief Checks if a key is pressed.
             *
             * @param code 		The Key Code to check.
             * @return true		The key is pressed.
             * @return false	The key is released.
             */
            bool IsKeyPressed(int code);
            /**
             * @brief Checks if a key is released.
             *
             * @param code		The Key Code to check.
             * @return true		The Key is released.
             * @return false	The Key is pressed.
             */
            bool IsKeyReleased(int code);

            /**
             * @brief Checks if a mouse key is pressed.
             *
             * @param code		The Mouse Key Code to check.
             * @return true		The Mouse Key is pressed.
             * @return false	The Mouse Key is released.
             */
            bool IsMouseKeyPressed(int code);
            /**
             * @brief Checks if a mouse key is released.
             *
             * @param code		The Mouse Key Code to check.
             * @return true		The Mouse Key is released.
             * @return false	The Mouse Key is pressed.
             */
            bool IsMouseKeyReleased(int code);

            /**
             * @brief Checks if a touch state is true.
             *
             * @param state		The state to check.
             * @return true		The state is true.
             * @return false	The state is false.
             */
            bool IsTouchState(int state);

            /**
             * @brief Get the Mouse position.
             *
             * @return int The X position of the mouse.
             */
            int GetMouseX() { return this->mMouseX; };
            /**
             * @brief Get the Mouse position.
             *
             * @return int The Y position of the mouse.
             */
            int GetMouseY() { return this->mMouseY; };

            /**
             * @brief Get the Touch Position.
             *
             * @return int The X position of the touch.
             */
            int GetTouchX() { return this->mTouchX; }
            /**
             * @brief Get the Touch Position.
             *
             * @return int The Y position of the touch.
             */
            int GetTouchY() { return this->mTouchY; }

            /**
             * @brief Resets all states to false.
             *
             */
            void ResetState();

        private:
            bool mKeys[API_INPUT_KEY_COUNT + 1];
            bool mMouseKeys[API_INPUT_MOUSE_BUTTON_COUNT + 1];

            int mMouseX, mMouseY;

            int mTouchX, mTouchY;
            bool mTouchState[API_INPUT_ANDROID_TOUCH_COUNT + 1];
    };

}  // namespace GEngine
