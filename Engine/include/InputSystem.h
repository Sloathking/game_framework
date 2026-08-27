//
// Created by sloath on 24-Aug-26.
//

#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "Math.h"
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_events.h>
#include <vector>
#include <map>

static constexpr int mMaxControllers = 4;

enum ButtonState
{
    ENone,
    EPressed,
    EReleased,
    EHeld
};

class KeyboardState
{
public:
    friend class InputSystem;

    // get just the bool t/f of key
    [[nodiscard]] bool GetKeyValue(SDL_Scancode keyCode) const;

    // get a state based on curr and prev frames
    [[nodiscard]] ButtonState GetKeyState(SDL_Scancode keyCode) const;

private:
    // curr state
    const bool* mCurrState{};

    // state prev frame
    bool mPrevState[SDL_SCANCODE_COUNT]{};

};

class MouseState
{
public:
    enum MouseButton
    {
        Left = SDL_BUTTON_LEFT,
        Middle = SDL_BUTTON_MIDDLE,
        Right = SDL_BUTTON_RIGHT,
        X1 = SDL_BUTTON_X1,
        X2 = SDL_BUTTON_X2
    };

    friend class InputSystem;

    // for mouse pos
    [[nodiscard]] const Vector2& GetPosition() const { return mMousePos; }

    // for buttons
    [[nodiscard]] bool GetButtonValue(MouseButton button) const;
    [[nodiscard]] ButtonState GetButtonState(MouseButton button) const;

    // for scroll wheel
    [[nodiscard]] Vector2 GetScrollWheel() const { return mScrollWheel; }

private:
    Vector2 mMousePos{0, 0};
    SDL_MouseButtonFlags mCurrButtons{0};
    SDL_MouseButtonFlags mPrevButtons{0};
    Vector2 mScrollWheel{0, 0};
    bool mIsRelative{false};
};

class ControllerState
{
public:
    friend class InputSystem;

    // for buttons
    [[nodiscard]] bool GetButtonValue(SDL_GamepadButton button) const;
    [[nodiscard]] ButtonState GetButtonState(SDL_GamepadButton button) const;

    // triggers
    [[nodiscard]] float GetLeftTrigger() const { return mLeftTrigger; }
    [[nodiscard]] float GetRightTrigger() const { return mRightTrigger; }

    [[nodiscard]] Vector2 GetLeftStick() const { return mLeftStick; }
    [[nodiscard]] Vector2 GetRightStick() const { return mRightStick; }


    [[nodiscard]] bool GetIsConnected() const { return mIsConnected; }

private:
    // curr/prev buttons
    Uint8 mCurrButtons[SDL_GAMEPAD_BUTTON_COUNT]{};
    Uint8 mPrevButtons[SDL_GAMEPAD_BUTTON_COUNT]{};

    // sticks
    Vector2 mLeftStick{};
    Vector2 mRightStick{};

    // triggers
    float mLeftTrigger{0.0f};
    float mRightTrigger{0.0f};

    // is this controller connected?
    bool mIsConnected{false};
};

struct InputState
{
    KeyboardState Keyboard;
    MouseState Mouse;
    std::vector<ControllerState> Controllers{mMaxControllers};
};

class InputSystem
{
public:
    bool Initialize(class Game* game);
    void Shutdown() const;

    // called right BEFORE SDL_PollEvents loop
    void PrepareForUpdate();

    // called right AFTER SDL_PollEvents loop
    void Update();

    // used to handle MouseWheel events
    void ProcessEvent(const SDL_Event& event);

    [[nodiscard]] const InputState& GetState() const { return mState; }

    void SetRelativeMouseMode(bool value);

    static ButtonState CheckButtonState(const bool& prevFrame, const bool& currFrame);

    [[nodiscard]] float Filter1D(int input) const;
    [[nodiscard]] Vector2 Filter2D(int inputX, int inputY) const;

private:
    const float deadZone{250.0f};
    const float deadZone2D{8000.0f};
    const float maxValue{30000.0f};

    Game* mGame{};
    InputState mState{};
    std::vector<SDL_Gamepad*> mGamepads{mMaxControllers};

};

#endif //INPUTSYSTEM_H