//
// Created by sloath on 21-Aug-26.
//

#include "../include/PhysicsInputComponent.h"

#include "../include/Actor.h"
#include "../include/InputSystem.h"

PhysicsInputComponent::PhysicsInputComponent(Actor* mOwner, const int updateOrder) : PhysicsMoveComponent(mOwner, updateOrder)
{

}

void PhysicsInputComponent::ProcessInput(const InputState& state)
{
    if (mUpdate)
    {
        // calc forward speed for MoveComponent
        if (state.Keyboard.GetKeyState(mForwardKey) == EPressed) AddForce(mOwner->GetForward() * 10000);
        if (state.Keyboard.GetKeyState(mBackKey) == EPressed) AddForce(mOwner->GetForward() * -10000);
        //SetForwardSpeed(forwardSpeed);

        // calc angular speed for MoveComponent
        float angularSpeed = 0.0f;
        if (state.Keyboard.GetKeyState(mClockwiseKey) == EPressed) angularSpeed += mMaxAngularSpeed;
        if (state.Keyboard.GetKeyState(mCounterClockwiseKey) == EPressed) angularSpeed -= mMaxAngularSpeed;
        SetAngularSpeed(angularSpeed);
    }
}