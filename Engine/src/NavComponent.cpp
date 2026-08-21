//
// Created by sloath on 20-Aug-26.
//

#include "../include/NavComponent.h"

#include "../include/Actor.h"
#include "../../Game/Tile.h"

NavComponent::NavComponent(Actor* owner, const int updateOrder) : MoveComponent(owner, updateOrder)
{

}

void NavComponent::Update(const float deltaTime)
{
    if (mNextNode)
    {
        // if we've reached the next point, advance along path
        if (const Vector2 diff = mOwner->GetPosition() - mNextNode->GetPosition(); Math::NearZero(diff.Length(), 2.0f))
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

void NavComponent::TurnTo(const Vector2& pos) const
{
    // vector from me to pos
    const Vector2 dir = pos - mOwner->GetPosition();
    // new angle is just atan2 of this dir vector (negate y because +y down)
    const float angle = Math::Atan2(-dir.y, dir.x);
    mOwner->SetRotation(angle);
}
