//
// Created by sloath on 21-Aug-26.
//

#include "../include/PhysicsInputComponent.h"

#include "../include/Actor.h"

PhysicsInputComponent::PhysicsInputComponent(Actor* mOwner, const int updateOrder) : PhysicsMoveComponent(mOwner, updateOrder)
{

}

void PhysicsInputComponent::HandleEvent(const SDL_Event& event)
{
    if (mUpdate)
    {
        // calc forward speed for MoveComponent
        if (event.key.key == mForwardKey) AddForce(mOwner->GetForward() * 10000);
        if (event.key.key == mBackKey) AddForce(mOwner->GetForward() * -10000);
        //SetForwardSpeed(forwardSpeed);

        // calc angular speed for MoveComponent
        float angularSpeed = 0.0f;
        if (event.key.key == mClockwiseKey) angularSpeed += mMaxAngularSpeed;
        if (event.key.key == mCounterClockwiseKey) angularSpeed -= mMaxAngularSpeed;
        SetAngularSpeed(angularSpeed);
    }
}