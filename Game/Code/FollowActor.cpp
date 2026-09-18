//
// Created by sloath on 18-Sep-26.
//

#include "FollowActor.h"
#include "Game.h"
#include <Engine/include/Renderer.h>
#include <Engine/include/InputSystem.h>
#include <Engine/include/MoveComponent.h>
#include <Engine/include/FollowCamera.h>
#include <Engine/include/MeshComponent.h>

FollowActor::FollowActor(Game* game) : Actor(game)
{
    SetPosition(Vector3(0.0f, 0.0f, -100.f));

    mMoveComp = new MoveComponent(this);

    mCam = new FollowCamera(this);
    mCam->SetHorizontalDist(350.0f);
    mCam->SetVerticalDist(150.0f);
    mCam->SetSpringConstant(0.5f);
    mCam->SetTargetDist(15.0f);
    mCam->SnapToIdeal();

    mMesh = new MeshComponent(this);;
    mMesh->SetMesh(game->GetRenderer()->GetMesh("Assets/RacingCar.gpmesh"));
}

void FollowActor::ActorInput(const InputState& state)
{
    float forwardSpeed = 0.0f;
    float angularSpeed = 0.0f;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_W) == EHeld) forwardSpeed += 400.0f;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_S) == EHeld) forwardSpeed -= 400.0f;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_D) == EHeld) angularSpeed += Math::Pi;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_A) == EHeld) angularSpeed -= Math::Pi;

    mMoveComp->SetForwardSpeed(forwardSpeed);
    mMoveComp->SetAngularSpeed(angularSpeed);

    // adjust horizontal distance of camera based on speed
    if (!Math::NearZero((forwardSpeed))) mCam->SetHorizontalDist(500.0f);
    else mCam->SetHorizontalDist(350.0f);
}

void FollowActor::SetVisible(const bool visible) const
{
    mMesh->SetVisible(visible);
}