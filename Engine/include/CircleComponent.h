//
// Created by sloath on 18-Aug-26.
//

#ifndef CIRCLECOMPONENT_H
#define CIRCLECOMPONENT_H

#include "Component.h"
#include "Math.h"

class CircleComponent : public Component
{
public:
    explicit CircleComponent(Actor* owner);

    [[nodiscard]] float GetRadius() const { return mRadius; }
    void SetRadius(const float radius) { mRadius = radius; }

    [[nodiscard]] const Vector2& GetCenter() const;

private:
    float mRadius{0.0f};
};

bool Intersect(const CircleComponent& a, const CircleComponent& b);

#endif //CIRCLECOMPONENT_H
