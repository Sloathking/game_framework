//
// Created by sloath on 17-Aug-26.
//

#ifndef MOVECOMPONENT_H
#define MOVECOMPONENT_H

#include "Component.h"
#include "Math.h"


class MoveComponent : public Component
{
public:
    explicit MoveComponent(Actor* owner, int updateOrder = 10);

    void Update(float deltaTime) override;

    [[nodiscard]] float GetAngularSpeed() const { return mAngularSpeed; }
    void SetAngularSpeed(const float speed) { mAngularSpeed = speed; }

    [[nodiscard]] float GetForwardSpeed() const { return mForwardSpeed; }
    void SetForwardSpeed(const float speed) { mForwardSpeed = speed; }

    [[nodiscard]] float GetMass() const {return mMass; }
    void SetMass(const float mass) { mMass = mass; }

    void AddForce(Vector2 force);

    void ClearVelocity() { mVelocity = Vector2(0,0); }

private:
    // controls rotation radians/s
    float mAngularSpeed{0.0};

    // controls forward movement units/s
    float mForwardSpeed{0.0};

    // Newtonian Physics stuff
    float mMass{0.0f};
    Vector2 mVelocity{Vector2(0.0f, 0.0f)};
    Vector2 mSumOfForces{Vector2(0.0f, 0.0f)};
};

#endif //MOVECOMPONENT_H