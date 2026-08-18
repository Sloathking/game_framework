//
// Created by sloath on 18-Aug-26.
//

#include "../include/CircleComponent.h"
#include "../include/Actor.h"

CircleComponent::CircleComponent(Actor* owner) : Component(owner)
{

}

const Vector2& CircleComponent::GetCenter() const
{
    return mOwner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
    // calc distance squared
    const Vector2 diff = a.GetCenter() - b.GetCenter();
    const float distSQ = diff.LengthSq();

    // calc sum of radii squared
    float radiiSQ = a.GetRadius() + b.GetRadius();
    radiiSQ *= radiiSQ;

    return distSQ <= radiiSQ;
}