//
// Created by sloath on 20-Aug-26.
//

#include "include/NavComponent.h"
#include "include/Actor2D.h"
#include "include/Tile.h"

NavComponent::NavComponent(Actor2D* owner, const int updateOrder) : MoveComponent(owner, updateOrder)
{

}

void NavComponent::Update(const float deltaTime)
{
    if (mNextNode)
    {
        // if we've reached the next point, advance along path
        if (const Vector2 diff = dynamic_cast<Actor2D*>(mOwner)->GetPosition() - mNextNode->GetPosition(); Math::NearZero(diff.Length(), 2.0f))
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
    const Vector2 dir = pos - dynamic_cast<Actor2D*>(mOwner)->GetPosition();
    // new angle is just atan2 of this dir vector
    const float angle = Math::Atan2(dir.y, dir.x);
    dynamic_cast<Actor2D*>(mOwner)->SetRotation(angle);
}
