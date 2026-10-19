//
// Created by sloath on 10/19/26.
//

#include "include/MoveComponent2D.h"
#include "include/Actor2D.h"

MoveComponent2D::MoveComponent2D(Actor2D* owner, const int updateOrder) : Component(owner, updateOrder) {}

void MoveComponent2D::Update(const float deltaTime)
{
    const auto owner = dynamic_cast<Actor2D*>(mOwner);
    if (!Math::NearZero(mAngularSpeed))
    {
        float rot = owner->GetRotation();
        rot += mAngularSpeed * deltaTime;
        owner->SetRotation(rot);
    }

    if (!Math::NearZero(mForwardSpeed))
    {
        Vector2 pos = owner->GetPosition();
        pos += owner->GetForward() * mForwardSpeed * deltaTime;
        owner->SetPosition(pos);
    }
}
