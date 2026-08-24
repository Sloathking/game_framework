//
// Created by sloath on 11-Aug-26.
//

#ifndef SHIP_H
#define SHIP_H

#include "../Engine/include/Actor.h"
#include "SDL3/SDL_events.h"

class Ship : public Actor
{
public:
    explicit Ship(Game* game);

    void UpdateActor(float deltaTime) override;
    void ActorInput(const InputState& state) override;

private:
    class SpriteComponent* mShipSprite;
    class PhysicsInputComponent* mInputComp;
    class CircleComponent* mCollider;

    float mLaserCooldown{0.0};
    float mInvisibleTimer{0.0};

};

#endif //SHIP_H