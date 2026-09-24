//
// Created by sloath on 24-Sep-26.
//

#include "include/Camera2D.h"

#include "include/Actor.h"

Camera2D::Camera2D(Actor* owner) : CameraComponent(owner)
{

}

void Camera2D::Update(float deltaTime)
{
    const Quaternion q(mOwner->GetRight(), mPitch);

    const Vector3 target = mOwner->GetPosition();
    const Vector3 eye = target + mOffset;
    const Vector3 up = Vector3::Transform(Vector3::UnitZ, q);

    const Matrix4 view = Matrix4::CreateLookAt(eye, target, up);
    SetViewMatrix(view);
}