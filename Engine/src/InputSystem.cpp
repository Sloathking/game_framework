//
// Created by sloath on 24-Aug-26.
//

#include "../include/InputSystem.h"
#include <SDL3/SDL.h>
#include "../include/Game.h"

bool InputSystem::Initialize(Game* game)
{
    bool success = true;

    // assign curr keyboard state ptr
    if ((success = mState.Keyboard.mCurrState = SDL_GetKeyboardState(nullptr)))
        memset(mState.Keyboard.mPrevState, 0, SDL_SCANCODE_COUNT);
    else
        SDL_Log("Unable to init KeyboardState");

    mGame = game;

    return success;
}

void InputSystem::Shutdown()
{

}

void InputSystem::PrepareForUpdate()
{
    memcpy(mState.Keyboard.mPrevState, mState.Keyboard.mCurrState, SDL_SCANCODE_COUNT);
    mState.Mouse.mPrevButtons = mState.Mouse.mCurrButtons;
}

void InputSystem::Update()
{
    mState.Keyboard.mCurrState = SDL_GetKeyboardState(nullptr);

    float x = 0, y = 0;
    if (mState.Mouse.mIsRelative)
        mState.Mouse.mCurrButtons = SDL_GetRelativeMouseState(&x, &y);
    else
        mState.Mouse.mCurrButtons = SDL_GetMouseState(&x, &y);
    mState.Mouse.mMousePos = Vector2(x, y);
}

void InputSystem::SetRelativeMouseMode(const bool value)
{
    SDL_SetWindowRelativeMouseMode(mGame->GetWindow(), value);
    mState.Mouse.mIsRelative = value;
}

// get just the bool t/f of key
[[nodiscard]] bool KeyboardState::GetKeyValue(const SDL_Scancode keyCode) const
{
    return mCurrState[keyCode];
}

// get a state based on curr and prev frames
[[nodiscard]] ButtonState KeyboardState::GetKeyState(const SDL_Scancode keyCode) const
{
    const bool prevFrame = mPrevState[keyCode];
    const bool currFrame = mCurrState[keyCode];

    if (!prevFrame)
    {
        if (!currFrame)
            return ENone;
        return EPressed;
    }
    if (!currFrame)
        return EReleased;
    return EHeld;
}

[[nodiscard]] bool MouseState::GetButtonValue(const MouseButton button) const
{
    return mCurrButtons and SDL_BUTTON_MASK(button);
}

[[nodiscard]] ButtonState MouseState::GetButtonState(const MouseButton button) const
{
    const bool prevFrame = mPrevButtons and SDL_BUTTON_MASK(button);
    const bool currFrame = mCurrButtons and SDL_BUTTON_MASK(button);

    if (!prevFrame)
    {
        if (!currFrame)
            return ENone;
        return EPressed;
    }
    if (!currFrame)
        return EReleased;
    return EHeld;
}
