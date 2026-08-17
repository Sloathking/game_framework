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
    void HandleEvent(const SDL_Event& event) override;

private:
    class SpriteComponent* mShipSprite;

};

#endif //SHIP_H