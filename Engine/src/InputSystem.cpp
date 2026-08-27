//
// Created by sloath on 24-Aug-26.
//

#include "../include/InputSystem.h"
#include "../include/Game.h"
#include <algorithm>

bool InputSystem::Initialize(Game* game)
{
    // keyboard
    mState.Keyboard.mCurrState = SDL_GetKeyboardState(nullptr);
    memset(mState.Keyboard.mPrevState, 0, SDL_SCANCODE_COUNT);

    // mouse
    mState.Mouse.mCurrButtons = 0;
    mState.Mouse.mPrevButtons = 0;

    // controllers
    int numJoysticks;
    const SDL_JoystickID* joysticks = SDL_GetGamepads(&numJoysticks);
    int currGamepad = 0;
    for (int joystick = 0; joystick < numJoysticks; ++joystick)
    {
        if (currGamepad >= mMaxControllers) break;

        // is this joystick a controller
        if (SDL_IsGamepad(joysticks[joystick]))
        {
            SDL_Gamepad* gamepad = SDL_OpenGamepad(joysticks[joystick]);
            mGamepads[currGamepad] = gamepad;
            mState.Controllers[currGamepad].mIsConnected = gamepad != nullptr;
            memset(mState.Controllers[currGamepad].mCurrButtons, 0, SDL_GAMEPAD_BUTTON_COUNT);
            memset(mState.Controllers[currGamepad].mPrevButtons, 0, SDL_GAMEPAD_BUTTON_COUNT);
            currGamepad++;
        }
    }

    // game ref, for NOW only used to change mouse mode from RELATIVE <- -> NONE
    mGame = game;

    return true;
}

void InputSystem::Shutdown() const
{
    // clean up gamepads
    for (SDL_Gamepad* gamepad : mGamepads)
        if (gamepad)
        {
            SDL_CloseGamepad(gamepad);
            gamepad = nullptr;
        }
}

void InputSystem::PrepareForUpdate()
{
    //keyboard
    memcpy(mState.Keyboard.mPrevState, mState.Keyboard.mCurrState, SDL_SCANCODE_COUNT);

    // mouse
    mState.Mouse.mPrevButtons = mState.Mouse.mCurrButtons;
    mState.Mouse.mScrollWheel = Vector2::Zero;

    // controllers
    for (auto& Controller : mState.Controllers)
        memcpy(Controller.mPrevButtons, Controller.mCurrButtons, SDL_GAMEPAD_BUTTON_COUNT);
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

    // controllers
    for (int gamepad = 0; gamepad < mGamepads.size(); gamepad++)
    {
        if (!mGamepads[gamepad]) continue;

        // update buttons
        for (int i = 0; i < SDL_GAMEPAD_BUTTON_COUNT; ++i)
            mState.Controllers[gamepad].mCurrButtons[i] = SDL_GetGamepadButton(mGamepads[gamepad], static_cast<SDL_GamepadButton>(i));

        // update triggers
        mState.Controllers[gamepad].mLeftTrigger = Filter1D(SDL_GetGamepadAxis(mGamepads[gamepad], SDL_GAMEPAD_AXIS_LEFT_TRIGGER));
        mState.Controllers[gamepad].mRightTrigger = Filter1D(SDL_GetGamepadAxis(mGamepads[gamepad], SDL_GAMEPAD_AXIS_RIGHT_TRIGGER));

        // update sticks
        mState.Controllers[gamepad].mLeftStick = Filter2D(
            SDL_GetGamepadAxis(mGamepads[gamepad], SDL_GAMEPAD_AXIS_LEFTX),
            -SDL_GetGamepadAxis(mGamepads[gamepad], SDL_GAMEPAD_AXIS_LEFTY)
            );
        mState.Controllers[gamepad].mRightStick = Filter2D(
            SDL_GetGamepadAxis(mGamepads[gamepad], SDL_GAMEPAD_AXIS_RIGHTX),
            -SDL_GetGamepadAxis(mGamepads[gamepad], SDL_GAMEPAD_AXIS_RIGHTY)
            );
    }
}

void InputSystem::ProcessEvent(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_EVENT_MOUSE_WHEEL:
        mState.Mouse.mScrollWheel = Vector2(event.wheel.x, event.wheel.y);
        break;
    case SDL_EVENT_GAMEPAD_REMOVED:
        {
            SDL_Gamepad* gamepad = SDL_GetGamepadFromID(event.gdevice.which);
            const auto it = std::find(mGamepads.begin(), mGamepads.end(), gamepad);
            const int index = static_cast<int>(std::distance(mGamepads.begin(), it));

            mGamepads[index] = nullptr;
            mState.Controllers[index].mIsConnected = gamepad != nullptr;
            SDL_CloseGamepad(gamepad);
            SDL_Log("Controller %i Removed", index + 1);
            break;
        }
    case SDL_EVENT_GAMEPAD_ADDED:
        {
            SDL_Gamepad* gamepad = SDL_OpenGamepad(event.gdevice.which);
            bool slotFound{false};
            for (int i = 0; i < mGamepads.size(); ++i)
            {
                if (mGamepads[i] == nullptr)
                {
                    mGamepads[i] = gamepad;
                    mState.Controllers[i].mIsConnected = gamepad != nullptr;
                    memset(mState.Controllers[i].mCurrButtons, 0, SDL_GAMEPAD_BUTTON_COUNT);
                    memset(mState.Controllers[i].mPrevButtons, 0, SDL_GAMEPAD_BUTTON_COUNT);
                    slotFound = true;
                    SDL_Log("Controller %i Added", i + 1);
                    break;
                }
            }
            if (!slotFound) SDL_CloseGamepad(gamepad);
            break;
        }
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
    float retVal{0.0f};

    // ignore input within dead zone
    if (const int absValue{input > 0 ? input : -input}; static_cast<float>(absValue) > deadZone)
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
    return mCurrButtons & SDL_BUTTON_MASK(button);
}

[[nodiscard]] ButtonState MouseState::GetButtonState(const MouseButton button) const
{
    const bool prevFrame = mPrevButtons & SDL_BUTTON_MASK(button);
    const bool currFrame = mCurrButtons & SDL_BUTTON_MASK(button);
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