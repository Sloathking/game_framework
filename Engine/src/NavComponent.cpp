//
// Created by sloath on 20-Aug-26.
//

#include "include/NavComponent.h"
#include "include/Actor.h"
#include "include/Tile.h"

NavComponent::NavComponent(Actor* owner, const int updateOrder) : MoveComponent(owner, updateOrder)
{

}

void NavComponent::Update(const float deltaTime)
{
    if (mNextNode)
    {
        // if we've reached the next point, advance along path
        if (const Vector3 diff = mOwner->GetPosition() - mNextNode->GetPosition(); Math::NearZero(diff.Length(), 2.0f))
        {
            mNextNode = mNextNode->GetParent();
            TurnTo(mNextNode->GetPosition());
        }
    }
    // this moves the actor forward
    MoveComponent::Update(deltaTime);
}

void NavComponent::StartPath(const Tile* start)
{
    mNextNode = start->GetParent();
    TurnTo(mNextNode->GetPosition());
}

void NavComponent::TurnTo(const Vector3& pos) const
{
    // vector from me to pos
    const Vector3 dir = pos - mOwner->GetPosition();
    // new angle is just atan2 of this dir vector

    Quaternion rot = mOwner->GetRotation();
    const float angle = Math::Atan2(dir.y, dir.x);
    const Quaternion inc(Vector3::UnitZ, angle);
    rot = Quaternion::Concatenate(rot, inc);

    mOwner->SetRotation(rot);
}
