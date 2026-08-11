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
        if (!mAnimTextures.empty())
        {
            // update the curr frame based on frame rate and delta time
            mCurrFrame += mAnimFPS * deltaTime;

            // wrap curr frame if needed
            while (mCurrFrame >= mAnimTextures.size())
                mCurrFrame -= mAnimTextures.size();

            // set curr texture
            SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
        }
}

// set textures used for anim
void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
    mAnimTextures = textures;
    if (!mAnimTextures.empty())
    {
        mCurrFrame = 0.0f;
        SetTexture(mAnimTextures[0]);
    }
}

// add animation to animation map, but DOES NOT update existing animations
void AnimSpriteComponent::AddAnimation(const int& num, const std::vector<SDL_Texture*>& texture)
{
    if (animations.contains(num)) return;
    animations[num] = texture;
}

// if able to update an animation in Animations returns TRUE, else FALSE
void AnimSpriteComponent::UpdateAnimation(const int& num, const std::vector<SDL_Texture*>& texture)
{
    animations[num] = texture;
}

// play animation in Animations
void AnimSpriteComponent::PlayAnimation(const int& num)
{
    SetAnimTextures(animations[num]);
    mAnimate = true;
}

// plan an animation in Animations once
void AnimSpriteComponent::OneshotAnimation(const std::string& name)
{

}