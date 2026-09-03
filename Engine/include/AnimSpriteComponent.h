//
// Created by sloath on 06-Aug-26.
//

#ifndef ANIMSPRITECOMPONENT_H
#define ANIMSPRITECOMPONENT_H

#include "SpriteComponent.h"
#include <vector>
#include <unordered_map>

class AnimSpriteComponent : public SpriteComponent
{
public:
    enum LoopingType { NO_LOOP, LOOP };

    explicit AnimSpriteComponent(Actor* owner, int drawOrder = 100);

    // update anim every frame
    void Update(float deltaTime) override;

    // add animation to Animations
    void AddAnimation(const int& num, LoopingType toLoop, const std::vector<SDL_Texture*>& textures);

    // update an animation in Animations
    void UpdateAnimation(const int& num, LoopingType toLoop, const std::vector<SDL_Texture*>& textures);

    // play animation in Animations
    void PlayAnimation(const int& num);

    // start playing animation on loop
    void StartAnimation() { mAnimate = true; };

    // stop animation
    void StopAnimation() { mAnimate = false; }

    // set / get anim FPS
    [[nodiscard]] float GetAnimFPS() const { return mAnimFPS; }
    void SetAnimFPS(const float fps) { mAnimFPS = fps; }

    // get num of current anim playing
    int GetCurrAnim() const { return mCurrAnim; }

private:
    // set textures used for anim
    void SetAnimTextures(const std::vector<SDL_Texture*>& textures);

    // map to hold animations
    std::unordered_map<int, std::pair<LoopingType, std::vector<SDL_Texture*>>> mAnimations{};

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

#endif //ANIMSPRITECOMPONENT_H