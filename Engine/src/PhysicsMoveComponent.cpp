//
// Created by sloath on 21-Aug-26.
//

#include "include/PhysicsMoveComponent.h"
#include "include/Actor.h"
#include "include/Math.h"

PhysicsMoveComponent::PhysicsMoveComponent(Actor* owner, const int updateOrder) : Component(owner, updateOrder)
{

}

void PhysicsMoveComponent::Update(const float deltaTime)
{
    // physics based movement
    Vector2 newPos = mOwner->GetPosition();
    Vector2 accel;
    // (semi-implicit) Euler Integration
    accel.x = mSumOfForces.x / mMass;
    accel.y = mSumOfForces.y / mMass;

    // update velocity
    mVelocity += accel * deltaTime;

    // update position
    newPos += mVelocity * deltaTime;
    mOwner->SetPosition(newPos);

    mSumOfForces = Vector2::Zero;

    // physics and non-physics
    if (!Math::NearZero(mAngularSpeed))
    {
        float rot = mOwner->GetRotation();
        rot += mAngularSpeed * deltaTime;
        mOwner->SetRotation(rot);
    }
}

void PhysicsMoveComponent::AddForce(const Vector2 force)
{
    mSumOfForces += force;
}