//
// Created by sloath on 06-Aug-26.
//
#include "../include/SpriteComponent.h"
#include "../include/Actor.h"
#include "../include/Game.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) : Component{owner}, mTexture{nullptr}, mDrawOrder{drawOrder}, mTexWidth{0}, mTexHeight{0}
{
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{

}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
    if (mTexture)
    {
        SDL_FRect dstRect{ mOwner->GetPosition().x, mOwner->GetPosition().y, mTexWidth * mOwner->GetScale(), mTexHeight * mOwner->GetScale() };
        SDL_FPoint center{ (mOwner->GetPosition().x + mTexWidth) * 0.5f, (mOwner->GetPosition().y + mTexHeight) * 0.5f };

        SDL_RenderTextureRotated(mOwner->GetGame()->GetRenderer(), mTexture, nullptr, &dstRect, -Math::ToDegrees(mOwner->GetRotation()), &center, SDL_FLIP_NONE);
    }
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
    mTexture = texture;
    mTexWidth = mTexture->w;
    mTexHeight = mTexture->h;
}