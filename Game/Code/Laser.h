//
// Created by sloath on 18-Aug-26.
//

#ifndef LASER_H
#define LASER_H

#include <Engine/include/Actor2D.h>

class Laser : public Actor2D
{
public:
    explicit Laser(Engine* game, Vector2 dir);

    void UpdateActor(float deltaTime) override;

private:
    class CircleComponent* mCircleComp;
    float mDeathTimer{1.0f};

};

#endif //LASER_H