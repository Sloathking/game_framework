//
// Created by sloath on 20-Aug-26.
//

#ifndef NAVCOMPONENT_H
#define NAVCOMPONENT_H

#include "MoveComponent.h"
#include "Math.h"

class NavComponent : public MoveComponent
{
public:
    explicit NavComponent(Actor* owner, int updateOrder = 10);

    void Update(float deltaTime) override;

    void StartPath(const class Tile* start);

    void TurnTo(const Vector2& pos) const;

private:
    const Tile* mNextNode{nullptr};

};


#endif //NAVCOMPONENT_H
