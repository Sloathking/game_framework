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

    void HandleEvent(const SDL_Event& event) override;

    // getters/setters
    [[nodiscard]] float GetMaxForwardSpeed() const { return mMaxForwardSpeed; }
    void SetMaxForwardSpeed(const float speed) { mMaxForwardSpeed = speed; }

    [[nodiscard]] float GetMaxAngularSpeed() const { return mMaxAngularSpeed; }
    void SetMaxAngularSpeed(const float speed) { mMaxAngularSpeed = speed; }

    [[nodiscard]] int GetForwardKey() const { return mForwardKey; }
    void SetForwardKey(const int key) { mForwardKey = key; }

    [[nodiscard]] int GetBackKey() const { return mBackKey; }
    void SetBackKey(const int key) { mBackKey = key; }

    [[nodiscard]] int GetClockwiseKey() const { return mClockwiseKey; }
    void SetClockwiseKey(const int key) { mClockwiseKey = key; }

    [[nodiscard]] int GetCounterClockwiseKey() const { return mCounterClockwiseKey; }
    void SetCounterClockwiseKey(const int key) { mCounterClockwiseKey = key; }

private:
    // max forward/angular speeds
    float mMaxForwardSpeed{0.0};
    float mMaxAngularSpeed{0.0};

    // keys for forward/back movement
    int mForwardKey{0};
    int mBackKey{0};

    // keys for angular movement
    int mClockwiseKey{0};
    int mCounterClockwiseKey{0};
};

#endif //INPUTCOMPONENT_H
