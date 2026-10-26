//
// Created by sloath on 10/19/26.
//

#include "include/MoveComponent2D.h"
#include "include/Actor2D.h"

MoveComponent2D::MoveComponent2D(Actor2D* owner, const int updateOrder) : Component2D(owner, updateOrder) {}

void MoveComponent2D::Update(const float deltaTime)
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

    if (!Math::NearZero(mStrafeSpeed))
    {
        Vector2  pos = mOwner->GetPosition();
        pos += mOwner->GetRight() * mStrafeSpeed * deltaTime;
        mOwner->SetPosition(pos);
    }
}
