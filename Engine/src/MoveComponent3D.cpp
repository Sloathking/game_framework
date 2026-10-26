//
// Created by sloath on 17-Aug-26.
//

#include "include/MoveComponent3D.h"
#include "include/Actor3D.h"
#include "include/Math.h"

MoveComponent3D::MoveComponent3D(Actor3D* owner, const int updateOrder) : Component3D(owner, updateOrder)
{

}

void MoveComponent3D::Update(const float deltaTime)
{
    if (!Math::NearZero(mAngularSpeed))
    {
        Quaternion rot = mOwner->GetRotation();
        const float angle = mAngularSpeed * deltaTime;
        const Quaternion inc(Vector3::UnitZ, angle);
        rot = Quaternion::Concatenate(rot, inc);
        mOwner->SetRotation(rot);
    }

    if (!Math::NearZero(mForwardSpeed) or !Math::NearZero(mStrafeSpeed) or !Math::NearZero(mVertSpeed))
    {
        Vector3 pos = mOwner->GetPosition();
        pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
        pos += mOwner->GetRight() * mStrafeSpeed * deltaTime;
        pos += Vector3::UnitZ * mVertSpeed * deltaTime;
        mOwner->SetPosition(pos);
    }
}
