//
// Created by sloath on 17-Aug-26.
//

#include "include/MoveComponent.h"
#include "include/Actor.h"
#include "include/Math.h"

MoveComponent::MoveComponent(Actor* owner, const int updateOrder) : Component(owner, updateOrder)
{

}

void MoveComponent::Update(const float deltaTime)
{
    // physics and non-physics
    if (!Math::NearZero(mAngularSpeed))
    {
        Quaternion rot = mOwner->GetRotation();
        const float angle = mAngularSpeed * deltaTime;
        const Quaternion inc(Vector3::UnitZ, angle);
        rot = Quaternion::Concatenate(rot, inc);
        mOwner->SetRotation(rot);
    }

    if (!Math::NearZero(mForwardSpeed))
    {
        Vector3 pos = mOwner->GetPosition();
        pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
        mOwner->SetPosition(pos);
    }
}