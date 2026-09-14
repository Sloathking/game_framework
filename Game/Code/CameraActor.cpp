//
// Created by sloath on 14-Sep-26.
//

#include "CameraActor.h"

#include <Engine/include/MoveComponent.h>

#include "Engine/include/Engine.h"
#include "Engine/include/InputSystem.h"
#include "Engine/include/Renderer.h"

CameraActor::CameraActor(Engine* game) : Actor(game)
{
    mMoveComp = new MoveComponent(this);
}

void CameraActor::UpdateActor(const float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    // compute new camera from this actor
    const Vector3 cameraPos = GetPosition();
    const Vector3 target = GetPosition() + GetForward() * 100.0f;
    const Vector3 up = Vector3::UnitZ;

    const Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
    GetGame()->GetRenderer()->SetViewMatrix(view);
}

void CameraActor::ActorInput(const InputState& state)
{
    float forwardSpeed = 0.0f;
    float angularSpeed = 0.0f;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_W)) forwardSpeed += 300.0f;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_S)) forwardSpeed -= 300.0f;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_D)) angularSpeed += Math::TwoPi;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_A)) angularSpeed -= Math::TwoPi;
    mMoveComp->SetForwardSpeed(forwardSpeed);
    mMoveComp->SetAngularSpeed(angularSpeed);

}