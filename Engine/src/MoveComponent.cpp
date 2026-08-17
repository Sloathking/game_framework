//
// Created by sloath on 17-Aug-26.
//

#include "../include/MoveComponent.h"

#include "../include/Actor.h"
#include "../include/Math.h"

MoveComponent::MoveComponent(Actor* owner, const int updateOrder) : Component(owner, updateOrder)
{

}

void MoveComponent::Update(const float deltaTime)
{
    if (!Math::NearZero(mAngularSpeed))
    {
        float rot = mOwner->GetRotation();
        rot += mAngularSpeed * deltaTime;
        mOwner->SetRotation(rot);
    }

    if (!Math::NearZero(mForwardSpeed))
    {
        Vector2 pos = mOwner->GetPosition();
        pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
        mOwner->SetPosition(pos);
    }
}