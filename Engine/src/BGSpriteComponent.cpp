//
// Created by sloath on 06-Aug-26.
//
#include "../include/BGSpriteComponent.h"
#include "../include/Actor.h"
#include "../include/Game.h"

BGSpriteComponent::BGSpriteComponent(Actor* owner, const int drawOrder) : SpriteComponent(owner, drawOrder), mScrollSpeed{0.0f}
{

}

// update draw override
void BGSpriteComponent::Update(const float deltaTime)
{
    SpriteComponent::Update(deltaTime);

    for (auto& bg : mBGTextures)
    {
        // update the x offset
        bg.mOffset.x += mScrollSpeed * deltaTime;

        // if this is completely off screen, reset offset to the right of the last bg tex
        if (bg.mOffset.x < -mScreenSize.x)
            bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
    }
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer, Vector2 offset, const SDL_FRect* clip, float width, float height)
{
    for (auto& bg : mBGTextures)
    {
        SDL_FRect dstRect;
        dstRect.w = mScreenSize.x;
        dstRect.h = mScreenSize.y;
        dstRect.x = mOwner->GetPosition().x - dstRect.w * 0.5f + bg.mOffset.x;
        dstRect.y = mOwner->GetPosition().y - dstRect.h * 0.5f + bg.mOffset.y;
        SDL_RenderTexture(renderer, bg.mTexture, nullptr, &dstRect);
    }
}

// set the texture used for the background
void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
    int count = 0;
    for (const auto tex : textures)
    {
        BGTexture temp;
        temp.mTexture = tex;
        temp.mOffset.x = count * mScreenSize.x;
        temp.mOffset.y = 0;
        mBGTextures.emplace_back(temp);
        count++;
    }
}