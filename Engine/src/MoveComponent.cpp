//
// Created by sloath on 17-Aug-26.
//

#include "include/MoveComponent.h"
#include "include/Actor2D.h"
#include "include/Math.h"

MoveComponent::MoveComponent(Actor2D* owner, const int updateOrder) : Component(owner, updateOrder)
{

}

void MoveComponent::Update(const float deltaTime)
{
    // physics and non-physics
    if (!Math::NearZero(mAngularSpeed))
    {
        float rot = dynamic_cast<Actor2D*>(mOwner)->GetRotation();
        rot += mAngularSpeed * deltaTime;
        dynamic_cast<Actor2D*>(mOwner)->SetRotation(rot);
    }

    if (!Math::NearZero(mForwardSpeed))
    {
        Vector2 pos = dynamic_cast<Actor2D*>(mOwner)->GetPosition();
        pos += dynamic_cast<Actor2D*>(mOwner)->GetForward() * mForwardSpeed * deltaTime;
        dynamic_cast<Actor2D*>(mOwner)->SetPosition(pos);
    }
}