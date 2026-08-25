//
// Created by sloath on 24-Aug-26.
//

#include "../include/InputSystem.h"

#include <ranges>
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

    // mouse
    mState.Mouse.mCurrButtons = 0;
    mState.Mouse.mPrevButtons = 0;

    // controller
    int numSticks;
    const SDL_JoystickID* joysticks = SDL_GetGamepads(&numSticks);
    /*for (int joystick = 0; joystick < numSticks; ++joystick)
    {
        // is this joystick a controller
        if (SDL_IsGamepad(joysticks[joystick]))
        {
            SDL_Gamepad* gamepad = SDL_OpenGamepad(joysticks[joystick]);
            /*if (!gamepad)
                SDL_Log("Unable to OpenGamepad! SDL_Error: %s", SDL_GetError());#1#
            mGamepads.emplace_back(gamepad);
        }
    }
    for (auto& gamepad : mGamepads)
    {
        mState.Controllers[gamepad].mIsConnected = gamepad;
        memset(mState.Controllers[gamepad].mCurrButtons, 0, SDL_GAMEPAD_BUTTON_COUNT);
        memset(mState.Controllers[gamepad].mPrevButtons, 0, SDL_GAMEPAD_BUTTON_COUNT);
    }*/

    // this stays for now, we'll see if I find a need to remove or adapt it later
   //mController = mGamepads[0];
    mController = SDL_OpenGamepad(joysticks[0]);
    mState.Controller.mIsConnected = mController != nullptr;
    memset(mState.Controller.mCurrButtons, 0, SDL_GAMEPAD_BUTTON_COUNT);
    memset(mState.Controller.mPrevButtons, 0, SDL_GAMEPAD_BUTTON_COUNT);

    // game ref, for NOW only used to change mouse mode from RELATIVE <- -> NONE
    mGame = game;

    return success;
}

void InputSystem::Shutdown()
{

}

void InputSystem::PrepareForUpdate()
{
    //keyboard
    memcpy(mState.Keyboard.mPrevState, mState.Keyboard.mCurrState, SDL_SCANCODE_COUNT);

    // mouse
    mState.Mouse.mPrevButtons = mState.Mouse.mCurrButtons;
    mState.Mouse.mScrollWheel = Vector2::Zero;

    // gamepad
    memcpy(mState.Controller.mPrevButtons, mState.Controller.mCurrButtons, SDL_GAMEPAD_BUTTON_COUNT);
    /*for (auto& gamepad : mGamepads)
        memcpy(mState.Controllers[gamepad].mPrevButtons, mState.Controllers[gamepad].mCurrButtons, SDL_GAMEPAD_BUTTON_COUNT);*/
}

void InputSystem::Update()
{
    // keyboard
    mState.Keyboard.mCurrState = SDL_GetKeyboardState(nullptr);

    // mouse
    float x = 0, y = 0;
    if (mState.Mouse.mIsRelative)
        mState.Mouse.mCurrButtons = SDL_GetRelativeMouseState(&x, &y);
    else
        mState.Mouse.mCurrButtons = SDL_GetMouseState(&x, &y);
    mState.Mouse.mMousePos = Vector2(x, y);

    // controller
    for (int i = 0; i < SDL_GAMEPAD_BUTTON_COUNT; ++i)
        mState.Controller.mCurrButtons[i] = SDL_GetGamepadButton(mController, static_cast<SDL_GamepadButton>(i));

    mState.Controller.mLeftTrigger = Filter1D(SDL_GetGamepadAxis(mController, SDL_GAMEPAD_AXIS_LEFT_TRIGGER));
    mState.Controller.mRightTrigger = Filter1D(SDL_GetGamepadAxis(mController, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER));
    mState.Controller.mLeftStick = Filter2D(
        SDL_GetGamepadAxis(mController, SDL_GAMEPAD_AXIS_LEFTX),
        -SDL_GetGamepadAxis(mController, SDL_GAMEPAD_AXIS_LEFTY)
        );
    mState.Controller.mRightStick = Filter2D(
        SDL_GetGamepadAxis(mController, SDL_GAMEPAD_AXIS_RIGHTX),
        -SDL_GetGamepadAxis(mController, SDL_GAMEPAD_AXIS_RIGHTY)
        );
    /*for (auto& gamepad : mGamepads)
    {
        for (int i = 0; i < SDL_GAMEPAD_BUTTON_COUNT; ++i)
            mState.Controllers[gamepad].mCurrButtons[i] = SDL_GetGamepadButton(gamepad, static_cast<SDL_GamepadButton>(i));

        mState.Controllers[gamepad].mLeftTrigger = Filter1D(SDL_GetGamepadAxis(gamepad, SDL_GAMEPAD_AXIS_LEFT_TRIGGER));
        mState.Controllers[gamepad].mRightTrigger = Filter1D(SDL_GetGamepadAxis(gamepad, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER));
        mState.Controllers[gamepad].mLeftStick = Filter2D(
            SDL_GetGamepadAxis(gamepad, SDL_GAMEPAD_AXIS_LEFTX),
            -SDL_GetGamepadAxis(gamepad, SDL_GAMEPAD_AXIS_LEFTY)
            );
        mState.Controllers[gamepad].mRightStick = Filter2D(
            SDL_GetGamepadAxis(gamepad, SDL_GAMEPAD_AXIS_RIGHTX),
            -SDL_GetGamepadAxis(gamepad, SDL_GAMEPAD_AXIS_RIGHTY)
            );
    }*/
}

void InputSystem::ProcessEvent(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_EVENT_MOUSE_WHEEL:
        mState.Mouse.mScrollWheel = Vector2(event.wheel.x, event.wheel.y);
        break;
    /*case SDL_EVENT_GAMEPAD_REMOVED:
        {
            SDL_Gamepad* gamepad = SDL_OpenGamepad(event.gdevice.which);
            int counter = 0;
            for (auto* pad : mGamepads)
            {
                if (pad == gamepad)
                {
                    mGamepads.erase(pad);
                }
                counter++;
            }
            const auto it = std::ranges::find(mGamepads.begin(), mGamepads.end(), gamepad);
            mGamepads.erase(it);
            mState.Controllers.erase(*it);
            SDL_Log("Controller Removed");
            break;
        }
    case SDL_EVENT_GAMEPAD_ADDED:
        {
            // open game pad, add game pad to Vector, add to map, init info
            SDL_Gamepad* gamepad = SDL_OpenGamepad(event.gdevice.which);
            if (!gamepad)
                SDL_Log("Unable to OpenGamepad! SDL_Error: %s", SDL_GetError());
            mGamepads.emplace_back(gamepad);

            mState.Controllers[gamepad].mIsConnected = gamepad != nullptr;
            memset(mState.Controllers[gamepad].mCurrButtons, 0, SDL_GAMEPAD_BUTTON_COUNT);
            memset(mState.Controllers[gamepad].mPrevButtons, 0, SDL_GAMEPAD_BUTTON_COUNT);
            SDL_Log("Controller Added");
            break;
        }*/
    default:
        break;
    }
}

void InputSystem::SetRelativeMouseMode(const bool value)
{
    SDL_SetWindowRelativeMouseMode(mGame->GetWindow(), value);
    mState.Mouse.mIsRelative = value;
}

ButtonState InputSystem::CheckButtonState(const bool& prevFrame, const bool& currFrame)
{
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

float InputSystem::Filter1D(const int input) const
{
    float retVal = 0.0f;

    // take abs value of input
    int absValue = input > 0 ? input : -input;

    // ignore input within dead zone
    if (static_cast<float>(absValue) > deadZone)
    {
        // compute fraction value between dead zone and maxvalue
        retVal = (static_cast<float>(absValue) - deadZone) / (maxValue - deadZone);

        // make sure sign matches orig value
        retVal = input > 0 ? retVal : -1.0f * retVal;

        // clamp between -1.0f and 1.0f
        retVal = Math::Clamp(retVal, -1.0f, 1.0f);
    }
    return retVal;
}

Vector2 InputSystem::Filter2D(const int inputX, const int inputY) const
{
    // make into 2D vector
    Vector2 dir(static_cast<float>(inputX), static_cast<float>(inputY));

    // if length < dead zne, no input
    if (const float length = dir.Length(); length < deadZone2D) dir = Vector2::Zero;
    else
    {
        // calc fraction value between dead zone and max value circles
        float f = (length - deadZone2D) / (maxValue - deadZone2D);
        // clamp f: 0.0-1.0f
        f = Math::Clamp(f, 0.0f, 1.0f);
        // normalize vector, then scale it to fractional length
        dir *= f / length;
    }
    return dir;
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
    return InputSystem::CheckButtonState(prevFrame, currFrame);
}

[[nodiscard]] bool MouseState::GetButtonValue(const MouseButton button) const
{
    return mCurrButtons and SDL_BUTTON_MASK(button);
}

[[nodiscard]] ButtonState MouseState::GetButtonState(const MouseButton button) const
{
    SDL_Log("GetButtonState");
    const bool prevFrame = mPrevButtons and SDL_BUTTON_MASK(button);
    const bool currFrame = mCurrButtons and SDL_BUTTON_MASK(button);
    return InputSystem::CheckButtonState(prevFrame, currFrame);
}

[[nodiscard]] bool ControllerState::GetButtonValue(const SDL_GamepadButton button) const
{
    return mCurrButtons[button];
}

[[nodiscard]] ButtonState ControllerState::GetButtonState(const SDL_GamepadButton button) const
{
    const bool prevFrame = mPrevButtons[button];
    const bool currFrame = mCurrButtons[button];
    return InputSystem::CheckButtonState(prevFrame, currFrame);
}