//
// Created by sloath on 11-Aug-26.
//

#ifndef SKELETON_H
#define SKELETON_H

#include "../Engine/include/Actor.h"
#include <SDL3/SDL_Events.h>

enum animNames { DEFAULT = 0, WALKING = 1, RUNNING = 2, JUMPING = 3, PUNCH = 4 };

class Skeleton : public Actor
{
public:
    explicit Skeleton(Game* game);

    void UpdateActor(float deltaTime) override;
    void ActorInput(const InputState& state) override;

private:
    class AnimSpriteComponent* mAnimSprite;

};


#endif //SKELETON_H
