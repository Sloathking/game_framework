//
// Created by sloath on 17-Aug-26.
//

#ifndef ASTEROID_H
#define ASTEROID_H

#include "../../Engine/include/Actor.h"


class Asteroid : public Actor
{
public:
    explicit Asteroid(Engine* game);
    ~Asteroid() override;

    [[nodiscard]] class CircleComponent* GetCircle() const { return mCircleComp; }

private:
    class PhysicsMoveComponent* mMoveComp;
    CircleComponent* mCircleComp;

};


#endif //ASTEROID_H
