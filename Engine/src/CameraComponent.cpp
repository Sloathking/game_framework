//
// Created by sloath on 27-Aug-26.
//

#include "../include/CameraComponent.h"

#include "../include/Actor.h"

CameraComponent::CameraComponent(Actor* owner, const int updateOrder, const float viewWidth, const float viewHeight) : Component(owner, updateOrder)
{
    const Vector2 ownerPos = owner->GetPosition();
    mView = new SDL_FRect{.x = ownerPos.x, .y = ownerPos.y, .w = viewWidth, .h = viewHeight};
}

void CameraComponent::Update(float deltaTime)
{
    mPosition = mOwner->GetPosition();
}
