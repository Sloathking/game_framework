//
// Created by sloath on 17-Aug-26.
//

#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "MoveComponent.h"

class InputComponent : public MoveComponent
{
public:
    explicit InputComponent(Actor* mOwner, int updateOrder = 10);

    void ProcessInput(const InputState& state) override;

    // getters/setters
    [[nodiscard]] float GetMaxForwardSpeed() const { return mMaxForwardSpeed; }
    void SetMaxForwardSpeed(const float speed) { mMaxForwardSpeed = speed; }

    [[nodiscard]] float GetMaxAngularSpeed() const { return mMaxAngularSpeed; }
    void SetMaxAngularSpeed(const float speed) { mMaxAngularSpeed = speed; }

    [[nodiscard]] SDL_Scancode GetForwardKey() const { return mForwardKey; }
    void SetForwardKey(const SDL_Scancode key) { mForwardKey = key; }

    [[nodiscard]] SDL_Scancode GetBackKey() const { return mBackKey; }
    void SetBackKey(const SDL_Scancode key) { mBackKey = key; }

    [[nodiscard]] SDL_Scancode GetClockwiseKey() const { return mClockwiseKey; }
    void SetClockwiseKey(const SDL_Scancode key) { mClockwiseKey = key; }

    [[nodiscard]] SDL_Scancode GetCounterClockwiseKey() const { return mCounterClockwiseKey; }
    void SetCounterClockwiseKey(const SDL_Scancode key) { mCounterClockwiseKey = key; }

private:
    // max forward/angular speeds
    float mMaxForwardSpeed{0.0};
    float mMaxAngularSpeed{0.0};

    // keys for forward/back movement
    SDL_Scancode mForwardKey{};
    SDL_Scancode mBackKey{};
    // keys for angular movement
    SDL_Scancode mClockwiseKey{};
    SDL_Scancode mCounterClockwiseKey{};
};

#endif //INPUTCOMPONENT_H
