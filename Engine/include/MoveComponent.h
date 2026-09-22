//
// Created by sloath on 17-Aug-26.
//

#ifndef MOVECOMPONENT_H
#define MOVECOMPONENT_H

#include "Component.h"

class MoveComponent : public Component
{
public:
    explicit MoveComponent(class Actor* owner, int updateOrder = 10);

    void Update(float deltaTime) override;

    [[nodiscard]] float GetForwardSpeed() const { return mForwardSpeed; }
    void SetForwardSpeed(const float speed) { mForwardSpeed = speed; }

    [[nodiscard]] float GetVertSpeed() const { return mVertSpeed; }
    void SetVertSpeed(const float speed) { mVertSpeed = speed; }

    [[nodiscard]] float GetStrafeSpeed() const { return mStrafeSpeed; }
    void SetStrafeSpeed(const float speed) { mStrafeSpeed = speed; }

    [[nodiscard]] float GetAngularSpeed() const { return mAngularSpeed; }
    void SetAngularSpeed(const float speed) { mAngularSpeed = speed; }
    //
    // void IncreaseHeight() const;
    // void DecreaseHeight() const;

private:
    // controls forward movement units/s
    float mForwardSpeed{0.0f};

    // controls vertical speed
    float mVertSpeed{0.0f};

    // controls strafe speed
    float mStrafeSpeed{0.0f};

    // controls rotation radians/s
    float mAngularSpeed{0.0f};

};

#endif //MOVECOMPONENT_H