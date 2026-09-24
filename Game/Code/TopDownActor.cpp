//
// Created by sloath on 24-Sep-26.
//

#include "TopDownActor.h"
#include "Game.h"
#include <Engine/include/Camera2D.h>
#include <Engine/include/MoveComponent.h>
#include <Engine/include/InputSystem.h>

TopDownActor::TopDownActor(Game* game) : Actor(game)
{
    mCam = new Camera2D(this);
    mCam->SetOffset(mCamOffset);
    mCam->SetPitch(Math::Pi / 2.0f);

    mMoveComp = new MoveComponent(this);
}

void TopDownActor::UpdateActor(const float deltaTime)
{
    Actor::UpdateActor(deltaTime);
}

void TopDownActor::ActorInput(const InputState& state)
{
    if (state.Mouse.GetButtonState(MouseState::Right) == EPressed)
        GetGame()->SetRelativeMouseMode(true);
    if (state.Mouse.GetButtonState(MouseState::Right) == EReleased)
        GetGame()->SetRelativeMouseMode(false);

    float forwardSpeed = 0.0;
    float strafeSpeed = 0.0f;
    if (state.Mouse.GetButtonState(MouseState::Right) == EHeld)
    {
        const Vector2 mouseChange = state.Mouse.GetPosition();
        SDL_Log("X: %f | Y: %f", mouseChange.x, mouseChange.y);
        // strafeSpeed -= mouseChange.x * 10.0f;
        // forwardSpeed += mouseChange.y * 10.0f;
    }
    else
    {
        if (state.Keyboard.GetKeyState(SDL_SCANCODE_W) == EHeld) forwardSpeed += 300.0f;
        if (state.Keyboard.GetKeyState(SDL_SCANCODE_S) == EHeld) forwardSpeed -= 300.0f;

        if (state.Keyboard.GetKeyState(SDL_SCANCODE_D) == EHeld) strafeSpeed += 300.0f;
        if (state.Keyboard.GetKeyState(SDL_SCANCODE_A) == EHeld) strafeSpeed -= 300.0f;
    }


    if (const Vector2 mouseWheel = state.Mouse.GetScrollWheel(); mouseWheel.y != 0)
    {
        mCamOffset.z -= mouseWheel.y * mZoomScale;
        mCam->SetOffset(mCamOffset);
    }

    mMoveComp->SetForwardSpeed(forwardSpeed);
    mMoveComp->SetStrafeSpeed(strafeSpeed);
}

void TopDownActor::SetVisible(const bool visible) const
{
    if (visible)
        GetGame()->SetRelativeMouseMode(false);
    else
        GetGame()->SetRelativeMouseMode(true);
}
