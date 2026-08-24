//
// Created by sloath on 24-Aug-26.
//

#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <SDL3/SDL_keyboard.h>
#include "Math.h"

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
    const bool* mCurrState;

    // state prev frame
    Uint8 mPrevState[SDL_SCANCODE_COUNT];

};

class MouseState
{
public:
    enum MouseButton
    {
        Left = 1,
        Middle = 2,
        Right = 3,
        X1 = 4,
        X2 = 5
    };

    friend class InputSystem;

    // for mouse pos
    [[nodiscard]] const Vector2& GetPosition() const { return mMousePos; }

    // for buttons
    [[nodiscard]] bool GetButtonValue(MouseButton button) const;
    [[nodiscard]] ButtonState GetButtonState(MouseButton button) const;

private:
    Vector2 mMousePos{0, 0};
    Uint32 mCurrButtons{0};
    Uint32 mPrevButtons{0};
    bool mIsRelative{false};
};

struct InputState
{
    KeyboardState Keyboard{};
    MouseState Mouse;
};

class InputSystem
{
public:
    bool Initialize(class Game* game);
    void Shutdown();

    // called right BEFORE SDL_PollEvents loop
    void PrepareForUpdate();

    // called right AFTER SDL_PollEvents loop
    void Update();

    [[nodiscard]] const InputState& GetState() const { return mState; }

    void SetRelativeMouseMode(bool value);

private:
    Game* mGame;
    InputState mState{};

};

#endif //INPUTSYSTEM_H