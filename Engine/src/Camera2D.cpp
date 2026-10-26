//
// Created by sloath on 24-Sep-26.
//

#include "include/Camera2D.h"
#include "include/Actor2D.h"

Camera2D::Camera2D(Actor2D* owner, const int updateOrder) : Component2D(owner, updateOrder)
{

}

void Camera2D::Update(float deltaTime)
{

}

[[nodiscard]] Vector2 Camera2D::GetPosition() const
{
    return mOwner->GetPosition();
}