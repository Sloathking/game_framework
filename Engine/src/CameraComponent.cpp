//
// Created by sloath on 27-Aug-26.
//

#include "../include/CameraComponent.h"

#include "../include/Actor.h"

CameraComponent::CameraComponent(Actor* owner, const int updateOrder) : Component(owner, updateOrder)
{

}

void CameraComponent::Update(const float deltaTime)
{
    /*const Vector2 ownerPos = mOwner->GetPosition();
    mView->x = ownerPos.x - mWindowSize.x * 0.5f;
    mView->y = ownerPos.y - mWindowSize.y * 0.5f;*/
}

[[nodiscard]] Vector2 CameraComponent::GetPosition() const
{
    const Vector2 ownerPos = mOwner->GetPosition();
    Vector2 pos;
    pos.x = ownerPos.x - mWindowSize.x * 0.5f;
    pos.y = ownerPos.y - mWindowSize.y * 0.5f;
    return pos;
}