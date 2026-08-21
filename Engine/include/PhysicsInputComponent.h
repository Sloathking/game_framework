//
// Created by sloath on 21-Aug-26.
//

#ifndef PHYSICSINPUTCOMPONENT_H
#define PHYSICSINPUTCOMPONENT_H

#include "PhysicsMoveComponent.h"

class PhysicsInputComponent : public PhysicsMoveComponent
{
public:
    explicit PhysicsInputComponent(Actor* mOwner, int updateOrder = 10);

    void HandleEvent(const SDL_Event& event) override;

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
    float mMaxAngularSpeed{0.0};

    // keys for forward/back movement
    int mForwardKey{0};
    int mBackKey{0};

    // keys for angular movement
    int mClockwiseKey{0};
    int mCounterClockwiseKey{0};

};


#endif //PHYSICSINPUTCOMPONENT_H
