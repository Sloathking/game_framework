//
// Created by sloath on 24-Sep-26.
//

#include "include/Camera2D.h"
#include "include/Actor2D.h"

Camera2D::Camera2D(Actor2D* owner) : CameraComponent(owner)
{

}

void Camera2D::Update(float deltaTime)
{

}

[[nodiscard]] Vector2 Camera2D::GetPosition() const
{
    const auto ownerPos = dynamic_cast<Actor2D*>(mOwner)->GetPosition();
    Vector2 pos;
    pos.x = ownerPos.x - mWindowWidth * 0.5f;
    pos.y = ownerPos.y - mWindowHeight * 0.5f;
    return pos;
}