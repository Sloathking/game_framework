//
// Created by sloath on 06-Aug-26.
//

#ifndef CLION_GAME_PROGRAMMING_ANIMSPRITECOMPONENT_H
#define CLION_GAME_PROGRAMMING_ANIMSPRITECOMPONENT_H

#include "SpriteComponent.h"
#include <vector>

class AnimSpriteComponent : public SpriteComponent
{
public:
    AnimSpriteComponent(class Actor* owner, int drawOrder = 100);

    // update anim every frame
    void Update(float deltaTime) override;

    // set textures used for anim
    void SetAnimTextures(const std::vector<SDL_Texture*>& textures);

    // set / get anim FPS
    float GetAnimFPS() const { return mAnimFPS; }
    void SetAnimFPS(float fps) { mAnimFPS = fps; }

private:
    // all textures in the anim
    std::vector<SDL_Texture*> mAnimTextures;

    // current frame displayed
    float mCurrFrame;

    // anim frame rate
    float mAnimFPS;
};

#endif //CLION_GAME_PROGRAMMING_ANIMSPRITECOMPONENT_H