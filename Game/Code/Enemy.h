//
// Created by sloath on 21-Aug-26.
//

#ifndef ENEMY_H
#define ENEMY_H

#include "../../Engine/include/Actor.h"

class Enemy : public Actor
{
public:
    explicit Enemy(Engine* game);
    ~Enemy() override;

    void UpdateActor(float deltaTime) override;
    [[nodiscard]] class CircleComponent* GetCircle() const { return mCircleComp; }

private:
    CircleComponent* mCircleComp;

};

#endif //ENEMY_H