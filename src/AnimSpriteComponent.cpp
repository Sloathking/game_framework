//
// Created by sloath on 06-Aug-26.
//
#include "../include/AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(class Actor* owner, int drawOrder) : SpriteComponent(owner, drawOrder), mCurrFrame{ 0.0f }, mAnimFPS{ 24.0f }
{

}

// update anim every frame
void AnimSpriteComponent::Update(float deltaTime)
{
    SpriteComponent::Update(deltaTime);

    if (mAnimTextures.size() > 0)
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
    if (mAnimTextures.size() > 0)
    {
        mCurrFrame = 0.0f;
        SetTexture(mAnimTextures[0]);
    }
}