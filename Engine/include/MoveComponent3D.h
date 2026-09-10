//
// Created by sloath on 10-Sep-26.
//

#ifndef MOVECOMPONENT3D_H
#define MOVECOMPONENT3D_H

#include "Component.h"

class MoveComponent3D : public Component
{
public:
    explicit MoveComponent3D(class Actor3D* owner, int updateOrder = 10);

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

#endif //MOVECOMPONENT3D_H