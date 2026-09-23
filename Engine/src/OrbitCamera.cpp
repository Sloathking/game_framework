//
// Created by sloath on 22-Sep-26.
//

#include "include/OrbitCamera.h"
#include "include/Actor.h"
#include <SDL3/SDL_log.h>

OrbitCamera::OrbitCamera(Actor* owner) : CameraComponent(owner) {}

void OrbitCamera::Update(const float deltaTime)
{
    CameraComponent::Update(deltaTime);

    // create quaternion for yaw about world up
    const Quaternion yaw{Vector3::UnitZ, mYawSpeed * deltaTime};

    // transform offset and up by yaw
    mOffset = Vector3::Transform(mOffset, yaw);
    mUp = Vector3::Transform(mUp, yaw);

    // compute camera forward/right
    Vector3 forward = -1.0f * mOffset;
    forward.Normalize();
    Vector3 right = Vector3::Cross(mUp, forward);
    right.Normalize();

    constexpr float limit = Math::Pi / 4.0f;
    const float len = mOffset.Length();
    const float currPitch = std::asinf( Math::Clamp(mOffset.z / len, -1.0f, 1.0f));
    const float desiredPitch = currPitch + mPitchSpeed * deltaTime;
    const float clampedPitch = Math::Clamp(desiredPitch, -limit, limit);
    const float pitchDelta = clampedPitch - currPitch;

    // create quaternion for pitch about camera right
    const Quaternion pitch{right, pitchDelta};

    // transform camera offset and up by pitch
    mOffset = Vector3::Transform(mOffset, pitch);
    mUp = Vector3::Transform(mUp, pitch);

    // compute transform matrix
    const Vector3 target = mOwner->GetPosition();
    const Vector3 camPos = target + mOffset;
    const Matrix4 view = Matrix4::CreateLookAt(camPos, target, mUp);
    SetViewMatrix(view);
}