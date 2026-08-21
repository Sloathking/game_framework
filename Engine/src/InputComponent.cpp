//
// Created by sloath on 17-Aug-26.
//

#include "../include/InputComponent.h"

#include "../include/Actor.h"

InputComponent::InputComponent(Actor* mOwner, const int updateOrder) : MoveComponent(mOwner, updateOrder)
{

}

void InputComponent::HandleEvent(const SDL_Event& event)
{
    if (mUpdate)
    {
        float forwardSpeed = 0.0f;

        // calc forward speed for MoveComponent
        if (event.key.key == mForwardKey) forwardSpeed += mMaxForwardSpeed;
        if (event.key.key == mBackKey) forwardSpeed -= mMaxForwardSpeed;
        SetForwardSpeed(forwardSpeed);

        // calc angular speed for MoveComponent
        float angularSpeed = 0.0f;
        if (event.key.key == mClockwiseKey) angularSpeed += mMaxAngularSpeed;
        if (event.key.key == mCounterClockwiseKey) angularSpeed -= mMaxAngularSpeed;
        SetAngularSpeed(angularSpeed);
    }
}