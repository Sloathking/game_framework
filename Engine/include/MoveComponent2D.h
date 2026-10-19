//
// Created by sloath on 10/19/26.
//

#ifndef MOVECOMPONENT2D_H
#define MOVECOMPONENT2D_H

#include "Component.h"

class MoveComponent2D : public Component
{
public:
    explicit MoveComponent2D(class Actor2D* owner, int updateOrder = 10);

    void Update(float deltaTime) override;

    [[nodiscard]] float GetAngularSpeed() const { return mAngularSpeed; }
    void SetAngularSpeed(const float speed) { mAngularSpeed = speed; }

    [[nodiscard]] float GetForwardSpeed() const { return mForwardSpeed; }
    void SetForwardSpeed(const float speed) { mForwardSpeed = speed; }

private:
    float mAngularSpeed{0.0f};

    float mForwardSpeed{0.0f};

};

#endif // MOVECOMPONENT2D_H
