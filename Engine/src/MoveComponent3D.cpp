//
// Created by sloath on 17-Aug-26.
//

#include "include/MoveComponent3D.h"
#include "include/Actor3D.h"
#include "include/Math.h"

MoveComponent3D::MoveComponent3D(Actor3D* owner, const int updateOrder) : Component(owner, updateOrder)
{

}

void MoveComponent3D::Update(const float deltaTime)
{
    const auto owner = dynamic_cast<Actor3D*>(mOwner);
    if (!Math::NearZero(mAngularSpeed))
    {
        Quaternion rot = owner->GetRotation();
        const float angle = mAngularSpeed * deltaTime;
        const Quaternion inc(Vector3::UnitZ, angle);
        rot = Quaternion::Concatenate(rot, inc);
        owner->SetRotation(rot);
    }

    if (!Math::NearZero(mForwardSpeed) or !Math::NearZero(mStrafeSpeed) or !Math::NearZero(mVertSpeed))
    {
        Vector3 pos = owner->GetPosition();
        pos += owner->GetForward() * mForwardSpeed * deltaTime;
        pos += owner->GetRight() * mStrafeSpeed * deltaTime;
        pos += Vector3::UnitZ * mVertSpeed * deltaTime;
        owner->SetPosition(pos);
    }
}
