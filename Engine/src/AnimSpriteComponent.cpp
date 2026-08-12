//
// Created by sloath on 06-Aug-26.
//
#include "../include/AnimSpriteComponent.h"
#include <utility>

AnimSpriteComponent::AnimSpriteComponent(class Actor* owner, const int drawOrder) : SpriteComponent(owner, drawOrder), mCurrFrame{ 0.0f }, mAnimFPS{ 24.0f }
{

}

// update anim every frame
void AnimSpriteComponent::Update(const float deltaTime)
{
    SpriteComponent::Update(deltaTime);

    if (mAnimate)
    {
        if (!mAnimTextures.empty())
        {
            // update the curr frame based on frame rate and delta time
            mCurrFrame += mAnimFPS * deltaTime;

            // if playing looping animation
            if (animations[mCurrAnim].first == LOOP)
            {
                // wrap curr frame if needed
                while (mCurrFrame >= mAnimTextures.size())
                    mCurrFrame -= mAnimTextures.size();
            }
            // if playing non-looping animation
            else if (animations[mCurrAnim].first == NO_LOOP)
            {
                if (mCurrFrame >= mAnimTextures.size())
                {
                    mAnimate = false;
                    mCurrFrame = 0.0f;
                }
            }

            // set curr texture
            SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
        }
    }
}

// set textures used for anim
void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
    mAnimTextures = textures;
    if (!mAnimTextures.empty())
    {
        mCurrFrame = 0.0f;
        SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
    }
}

// add animation to animation map, but DOES NOT update existing animations
void AnimSpriteComponent::AddAnimation(const int& num, LoopingType toLoop, const std::vector<SDL_Texture*>& texture)
{
    if (animations.contains(num)) return;
    animations[num] = {toLoop, texture};
}

// if able to update an animation in Animations returns TRUE, else FALSE
void AnimSpriteComponent::UpdateAnimation(const int& num, LoopingType toLoop, const std::vector<SDL_Texture*>& texture)
{
    animations[num] = {toLoop, texture};
}

// play animation in Animations
void AnimSpriteComponent::PlayAnimation(const int& num)
{
    mCurrAnim = num;
    mAnimate = true;
    SetAnimTextures(animations[num].second);
}