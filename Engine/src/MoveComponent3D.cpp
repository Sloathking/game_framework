//
// Created by sloath on 10-Sep-26.
//

#include "include/MoveComponent3D.h"
#include "include/Actor3D.h"
#include "include/Math.h"

MoveComponent3D::MoveComponent3D(Actor3D* owner, const int updateOrder) : Component(owner, updateOrder)
{

}

void MoveComponent3D::Update(const float deltaTime)
{
    // physics and non-physics
    if (!Math::NearZero(mAngularSpeed))
    {
        Quaternion rot = dynamic_cast<Actor3D*>(mOwner)->GetRotation();
        const float angle = mAngularSpeed * deltaTime;
        // create quaternion for incremental rotation (rotate about UP axis)
        const Quaternion inc(Vector3::UnitZ, angle);
        // concatenate old and new quaternion
        rot = Quaternion::Concatenate(rot, inc);
        dynamic_cast<Actor3D*>(mOwner)->SetRotation(rot);
    }

    if (!Math::NearZero(mForwardSpeed))
    {
        Vector3 pos = dynamic_cast<Actor3D*>(mOwner)->GetPosition();
        pos += dynamic_cast<Actor3D*>(mOwner)->GetForward() * mForwardSpeed * deltaTime;
        dynamic_cast<Actor3D*>(mOwner)->SetPosition(pos);
    }
}