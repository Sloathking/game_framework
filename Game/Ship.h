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
    explicit Ship(class Game* game);

    void UpdateActor(float deltaTime) override;
    void HandleEvent(const SDL_Event& event);

    [[nodiscard]] float GetRightSpeed() const { return mRightSpeed; }
    [[nodiscard]] float GetDownSpeed() const { return mDownSpeed; }

private:
    float mRightSpeed{ 0 };
    float mDownSpeed{ 0 };
};


#endif //SHIP_H
