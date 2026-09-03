//
// Created by sloath on 17-Aug-26.
//

#include "include/InputComponent.h"
#include "include/InputSystem.h"

InputComponent::InputComponent(Actor* mOwner, const int updateOrder) : MoveComponent(mOwner, updateOrder)
{

}

void InputComponent::ProcessInput(const InputState& state)
{
    if (mUpdate)
    {
        float forwardSpeed = 0.0f;

        // calc forward speed for MoveComponent
        if (state.Keyboard.GetKeyState(mForwardKey) == EHeld) forwardSpeed += mMaxForwardSpeed;
        if (state.Keyboard.GetKeyState(mBackKey) == EHeld) forwardSpeed -= mMaxForwardSpeed;
        SetForwardSpeed(forwardSpeed);

        // calc angular speed for MoveComponent
        float angularSpeed = 0.0f;
        if (state.Keyboard.GetKeyState(mClockwiseKey) == EHeld) angularSpeed += mMaxAngularSpeed;
        if (state.Keyboard.GetKeyState(mCounterClockwiseKey) == EHeld) angularSpeed -= mMaxAngularSpeed;
        SetAngularSpeed(angularSpeed);
    }
}