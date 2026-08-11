//
// Created by sloath on 06-Aug-26.
//

#ifndef CLION_GAME_PROGRAMMING_ANIMSPRITECOMPONENT_H
#define CLION_GAME_PROGRAMMING_ANIMSPRITECOMPONENT_H

#include "SpriteComponent.h"
#include <vector>
#include <string>
#include <unordered_map>

class AnimSpriteComponent : public SpriteComponent
{
public:
    explicit AnimSpriteComponent(class Actor* owner, int drawOrder = 100);

    // update anim every frame
    void Update(float deltaTime) override;

    // add animation to Animations
    void AddAnimation(const int& num, const std::vector<SDL_Texture*>& texture);

    // update an animation in Animations
    void UpdateAnimation(const int& num, const std::vector<SDL_Texture*>& texture);

    // play animation in Animations
    void PlayAnimation(const int& num);

    // start playing animation on loop
    void StartAnimation() { mAnimate = true; };

    // stop animation
    void StopAnimation() { mAnimate = false; }

    // plan an animation in Animations once
    void OneshotAnimation(const std::string& name);

    // set / get anim FPS
    [[nodiscard]] float GetAnimFPS() const { return mAnimFPS; }
    void SetAnimFPS(const float fps) { mAnimFPS = fps; }

private:
    // set textures used for anim
    void SetAnimTextures(const std::vector<SDL_Texture*>& textures);

    // map to hold animations
    std::unordered_map<int, std::vector<SDL_Texture*>> animations{};

    // all textures in the anim
    std::vector<SDL_Texture*> mAnimTextures;

    // current animation
    int mCurrAnim{};

    // current frame displayed
    float mCurrFrame;

    // anim frame rate
    float mAnimFPS;

    // play animation
    bool mAnimate{ false };
};

#endif //CLION_GAME_PROGRAMMING_ANIMSPRITECOMPONENT_H