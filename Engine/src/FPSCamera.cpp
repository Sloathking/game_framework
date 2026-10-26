//
// Created by sloath on 17-Sep-26.
//

#include "include/FPSCamera.h"
#include "include/Actor3D.h"

FPSCamera::FPSCamera(Actor3D* owner) : CameraComponent(owner) {}

void FPSCamera::Update(const float deltaTime)
{
    CameraComponent::Update(deltaTime);
    const auto * owner = mOwner;
    // get position
    const Vector3 pos = owner->GetPosition();

    // calc current pitch, then rotate based on owner's Y
    mPitch += mPitchSpeed * deltaTime;
    mPitch = Math::Clamp(mPitch, -mMaxPitch, mMaxPitch);
    const Quaternion q(owner->GetRight(), mPitch);

    // create view matrix and assign to cam
    const Vector3 viewForward = Vector3::Transform(owner->GetForward(), q);
    const Vector3 target = pos + viewForward * 100.0f;
    const Vector3 up = Vector3::Transform(Vector3::UnitZ, q);

    const Matrix4 view = Matrix4::CreateLookAt(pos, target, up);
    SetViewMatrix(view);
}
