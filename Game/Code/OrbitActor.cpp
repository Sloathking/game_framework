//
// Created by sloath on 22-Sep-26.
//

#include "OrbitActor.h"
#include "Game.h"
#include <Engine/include/Renderer.h>
#include <Engine/include/InputSystem.h>
#include <Engine/include/MeshComponent.h>
#include <Engine/include/OrbitCamera.h>

OrbitActor::OrbitActor(Game* game) : Actor(game)
{
    mMeshComp = new MeshComponent(this);
    mMeshComp->SetMesh(game->GetRenderer()->GetMesh("Assets/RacingCar.gpmesh"));

    mCam = new OrbitCamera(this);
    mCam->SetOffset(mCamOffset);
}

void OrbitActor::ActorInput(const InputState& state)
{
    if (const float scrollWheel = state.Mouse.GetScrollWheel().y; scrollWheel != 0)
    {
        Vector3 camOffset = mCam->GetOffset();
        if (scrollWheel > 0)
            camOffset *= 0.9f;
        else
            camOffset *= 1.1f;
        mCam->SetOffset(camOffset);
    }

    const Vector2 mouseChange = state.Mouse.GetPosition();
    if (state.Mouse.GetButtonState(MouseState::Right) == EHeld)
    {
        constexpr int maxMouseSpeed = 500;
        constexpr float maxOrbitSpeed = Math::Pi * 8;

        // calc yaw
        float yawSpeed = 0.0f;
        if (mouseChange.x != 0)
        {
            yawSpeed = mouseChange.x / maxMouseSpeed;
            yawSpeed *= maxOrbitSpeed;
        }
        mCam->SetYawSpeed(yawSpeed);

        // cal pitch
        float pitchSpeed = 0.0f;
        if (mouseChange.y != 0)
        {
            pitchSpeed = mouseChange.y / maxMouseSpeed;
            pitchSpeed *= maxOrbitSpeed;
        }
        mCam->SetPitchSpeed(pitchSpeed);
    }
    else
    {
        mCam->SetYawSpeed(0.0f);
        mCam->SetPitchSpeed(0.0f);
    }
}

void OrbitActor::SetVisible(const bool visible) const
{
    mMeshComp->SetVisible(visible);
}
