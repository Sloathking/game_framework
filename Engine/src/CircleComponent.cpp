//
// Created by sloath on 18-Aug-26.
//

#include "include/CircleComponent.h"
#include "include/Actor.h"

CircleComponent::CircleComponent(Actor* owner) : Component(owner)
{

}

const Vector3& CircleComponent::GetCenter() const
{
    return mOwner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
    // calc distance squared
    const Vector3 aCenter = a.GetCenter();
    const Vector3 bCenter = b.GetCenter();
    const Vector2 diff = Vector2(aCenter.x, aCenter.y) - Vector2(bCenter.x, bCenter.y);
    const float distSQ = diff.LengthSq();

    // calc sum of radii squared
    float radiiSQ = a.GetRadius() + b.GetRadius();
    radiiSQ *= radiiSQ;

    return distSQ <= radiiSQ;
}