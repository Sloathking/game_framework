//
// Created by sloath on 18-Sep-26.
//

#include "include/FollowCamera.h"
#include "include/Actor3D.h"

FollowCamera::FollowCamera(Actor3D* owner) : CameraComponent(owner) {}

void FollowCamera::Update(const float deltaTime)
{
    CameraComponent::Update(deltaTime);

    // compute spring dampening
    const float dampening = 2.0f * Math::Sqrt(mSpringConstant);

    const Vector3 idealPos = ComputeCameraPos();

    const Vector3 diff = mActualPos - idealPos;
    const Vector3 accel = -mSpringConstant * diff - dampening * mVelocity;

    mVelocity += accel * deltaTime;
    mActualPos += mVelocity * deltaTime;

    const auto owner = dynamic_cast<Actor3D*>(mOwner);
    const Vector3 target = owner->GetPosition() + owner->GetForward() * mTargetDist;

    const Matrix4 view = Matrix4::CreateLookAt(mActualPos, target, Vector3::UnitZ);
    SetViewMatrix(view);
}

void FollowCamera::SnapToIdeal()
{
    const auto owner = dynamic_cast<Actor3D*>(mOwner);

    mActualPos = ComputeCameraPos();
    mVelocity = Vector3::Zero;
    const Vector3 target = owner->GetForward() + owner->GetForward() * mTargetDist;
    const Matrix4 view = Matrix4::CreateLookAt(mActualPos, target, Vector3::UnitZ);
    SetViewMatrix(view);
}

[[nodiscard]] Vector3 FollowCamera::ComputeCameraPos() const
{
    const auto owner = dynamic_cast<Actor3D*>(mOwner);

    // set camera position behind and above owner
    Vector3 cameraPos = owner->GetPosition();
    cameraPos -= owner->GetForward() * mHorizontalDist;
    cameraPos += Vector3::UnitZ * mVerticalDist;
    return cameraPos;
}