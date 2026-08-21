//
// Created by sloath on 21-Aug-26.
//

#ifndef PHYSICSMOVECOMPONENT_H
#define PHYSICSMOVECOMPONENT_H

#include "Component.h"
#include "Math.h"

class PhysicsMoveComponent : public Component
{
public:
    explicit PhysicsMoveComponent(Actor* owner, int updateOrder = 10);

    void Update(float deltaTime) override;

    [[nodiscard]] float GetMass() const {return mMass; }
    void SetMass(const float mass) { mMass = mass; }

    [[nodiscard]] float GetAngularSpeed() const { return mAngularSpeed; }
    void SetAngularSpeed(const float speed) { mAngularSpeed = speed; }

    void AddForce(Vector2 force);

    void ClearVelocity() { mVelocity = Vector2(0,0); }

private:
    // controls rotation radians/s
    float mAngularSpeed{0.0};

    // Newtonian Physics stuff
    float mMass{0.0f};
    Vector2 mVelocity{Vector2(0.0f, 0.0f)};
    Vector2 mSumOfForces{Vector2(0.0f, 0.0f)};
};


#endif //PHYSICSMOVECOMPONENT_H
