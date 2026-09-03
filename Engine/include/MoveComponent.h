//
// Created by sloath on 17-Aug-26.
//

#ifndef MOVECOMPONENT_H
#define MOVECOMPONENT_H

#include "Component.h"

class MoveComponent : public Component
{
public:
    explicit MoveComponent(Actor* owner, int updateOrder = 10);

    void Update(float deltaTime) override;

    [[nodiscard]] float GetAngularSpeed() const { return mAngularSpeed; }
    void SetAngularSpeed(const float speed) { mAngularSpeed = speed; }

    [[nodiscard]] float GetForwardSpeed() const { return mForwardSpeed; }
    void SetForwardSpeed(const float speed) { mForwardSpeed = speed; }

private:
    // controls rotation radians/s
    float mAngularSpeed{0.0};

    // controls forward movement units/s
    float mForwardSpeed{0.0};

};

#endif //MOVECOMPONENT_H