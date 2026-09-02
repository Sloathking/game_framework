//
// Created by sloath on 21-Aug-26.
//

#ifndef BULLET_H
#define BULLET_H

#include "../../Engine/include/Actor.h"

class Bullet : public Actor
{
public:
    explicit Bullet(Game* game);
    void UpdateActor(float deltaTime) override;

private:
    class CircleComponent* mCircleComp;
    float mLiveTime{0.0f};
};


#endif //BULLET_H
