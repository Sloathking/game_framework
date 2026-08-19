//
// Created by sloath on 17-Aug-26.
//

#include "../include/MoveComponent.h"

#include "../include/Actor.h"
#include "../include/Math.h"
#include "SDL3/SDL_log.h"

MoveComponent::MoveComponent(Actor* owner, const int updateOrder) : Component(owner, updateOrder)
{

}

void MoveComponent::Update(const float deltaTime)
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

/*  // non-physics
    if (!Math::NearZero(mForwardSpeed))
    {
        Vector2 pos = mOwner->GetPosition();
        pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
        mOwner->SetPosition(pos);
    }
*/
}

void MoveComponent::AddForce(const Vector2 force)
{
    mSumOfForces += force;
}