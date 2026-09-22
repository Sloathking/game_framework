//
// Created by sloath on 17-Sep-26.
//

#include "FPSActor.h"
#include "Game.h"
#include <Engine/include/Renderer.h>
#include <Engine/include/FPSCamera.h>
#include <Engine/include/InputSystem.h>
#include <Engine/include/MoveComponent.h>
#include <Engine/include/MeshComponent.h>


FPSActor::FPSActor(Game* game) : Actor(game)
{
    mMoveComp = new MoveComponent(this);
    mMoveComp->SetVertSpeed(10.0f);

    mCam = new FPSCamera(this);

    mFPSModel = new Actor(game);
    mFPSModel->SetScale(0.75f);
    mMesh = new MeshComponent(mFPSModel);
    mMesh->SetMesh(game->GetRenderer()->GetMesh("Assets/Rifle.gpmesh"));
}

void FPSActor::UpdateActor(const float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    // update position of FPS model relative to actor position
    const auto modelOffset{Vector3(20.0f, 10.0f, -10.0f)};
    Vector3 modelPos = GetPosition();
    modelPos += GetForward() * modelOffset.x;
    modelPos += GetRight() * modelOffset.y;
    modelPos.z += modelOffset.z;
    mFPSModel->SetPosition(modelPos);

    Quaternion q = GetRotation();
    q = Quaternion::Concatenate(q, Quaternion(GetRight(), mCam->GetPitch()));
    mFPSModel->SetRotation(q);
}

void FPSActor::ActorInput(const InputState& state)
{
    float forwardSpeed = 0.0;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_W) == EHeld) forwardSpeed += 300.0f;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_S) == EHeld) forwardSpeed -= 300.0f;

    float strafeSpeed = 0.0f;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_D) == EHeld) strafeSpeed += 300.0f;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_A) == EHeld) strafeSpeed -= 300.0f;

    float vertSpeed = 0.0f;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == EHeld) vertSpeed += 100.0f;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_LCTRL) == EHeld) vertSpeed -= 100.0f;

    constexpr int maxMouseSpeed = 500;
    const Vector2 mouseChange = state.Mouse.GetPosition();
    constexpr float maxAngularSpeed = Math::Pi * 8;

    float angularSpeed = 0.0f;
    if (mouseChange.x != 0)
    {
        angularSpeed = mouseChange.x / maxMouseSpeed;
        angularSpeed *= maxAngularSpeed;
    }

    constexpr float maxPitchSpeed = Math::Pi * 8;
    float pitchSpeed = 0.0f;
    if (mouseChange.y != 0)
    {
        pitchSpeed = mouseChange.y / maxMouseSpeed;
        pitchSpeed *= maxPitchSpeed;
    }

    if (state.Keyboard.GetKeyState(SDL_SCANCODE_LSHIFT) == EHeld)
    {
        forwardSpeed *= 4;
        vertSpeed *= 4;
        strafeSpeed *= 4;
    }
    mMoveComp->SetForwardSpeed(forwardSpeed);
    mMoveComp->SetVertSpeed(vertSpeed);
    mMoveComp->SetStrafeSpeed(strafeSpeed);
    mMoveComp->SetAngularSpeed(angularSpeed);

    mCam->SetPitchSpeed(pitchSpeed);

    if (state.Keyboard.GetKeyState(SDL_SCANCODE_LALT) == EPressed)
    {
        SetPosition(Vector3::Zero);
        SetRotation(Quaternion::Identity);
    }
}

void FPSActor::SetVisible(const bool visible) const
{
    mMesh->SetVisible(visible);
}
