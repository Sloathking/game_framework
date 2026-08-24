//
// Created by sloath on 21-Aug-26.
//

#ifndef TOWER_H
#define TOWER_H

#include "../Engine/include/Actor.h"

class Tower : public Actor
{
public:
    explicit Tower(Game* game);
    void UpdateActor(float deltaTime) override;

private:
    class MoveComponent* mMoveComp;

    float mNextAttack{0.0f};
    const float AttackTime = 2.5f;
    const float AttackRange = 100.0f;

};

#endif //TOWER_H