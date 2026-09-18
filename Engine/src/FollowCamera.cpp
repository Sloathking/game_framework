//
// Created by sloath on 18-Sep-26.
//

#include "include/FollowCamera.h"

#include "include/Actor.h"

FollowCamera::FollowCamera(Actor* owner) : CameraComponent(owner)
{

}

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

    const Vector3 target = mOwner->GetPosition() + mOwner->GetForward() * mTargetDist;

    const Matrix4 view = Matrix4::CreateLookAt(mActualPos, target, Vector3::UnitZ);
    SetViewMatrix(view);
}

void FollowCamera::SnapToIdeal()
{
    mActualPos = ComputeCameraPos();
    mVelocity = Vector3::Zero;
    const Vector3 target = mOwner->GetForward() + mOwner->GetForward() * mTargetDist;
    const Matrix4 view = Matrix4::CreateLookAt(mActualPos, target, Vector3::UnitZ);
    SetViewMatrix(view);
}

[[nodiscard]] Vector3 FollowCamera::ComputeCameraPos() const
{
    // set camera position behind and above owner
    Vector3 cameraPos = mOwner->GetPosition();
    cameraPos -= mOwner->GetForward() * mHorizontalDist;
    cameraPos += Vector3::UnitZ * mVerticalDist;
    return cameraPos;
}