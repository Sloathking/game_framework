//
// Created by sloath on 06-Aug-26.
//
#include "../include/SpriteComponent.h"
#include "../include/Actor.h"
#include "../include/Game.h"

SpriteComponent::SpriteComponent(Actor* owner, const int drawOrder) : Component{owner}, mTexture{nullptr}, mDrawOrder{drawOrder}, mTexWidth{0}, mTexHeight{0}
{
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() = default;

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
    if (mTexture)
    {
        const SDL_FRect dstRect{ .x = mOwner->GetPosition().x, .y = mOwner->GetPosition().y, .w = mTexWidth * mOwner->GetScale(), .h = mTexHeight * mOwner->GetScale() };
        const SDL_FPoint center{ .x = (mOwner->GetPosition().x + mTexWidth) * 0.5f, .y = (mOwner->GetPosition().y + mTexHeight) * 0.5f };

        SDL_RenderTextureRotated(mOwner->GetGame()->GetRenderer(), mTexture, nullptr, &dstRect, -Math::ToDegrees(mOwner->GetRotation()), &center, SDL_FLIP_NONE);
    }
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
    mTexture = texture;
    mTexWidth = mTexture->w;
    mTexHeight = mTexture->h;
}