//
// Created by sloath on 06-Aug-26.
//
#include "../include/SpriteComponent.h"
#include "../include/Actor.h"
#include "../include/Game.h"

SpriteComponent::SpriteComponent(Actor* owner, const int drawOrder) : Component{owner}, mDrawOrder{drawOrder}
{
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer, const SDL_FRect* clip,
    const float width, const float height)
{
    SDL_Log("%d", mTexWidth);
    SDL_Log("%f", anchorOffset.x);
    //Set texture position
    SDL_FRect dstRect{ .x = mOwner->GetPosition().x + anchorOffset.x + mXOffset, .y = mOwner->GetPosition().y + mYOffset,
        .w = static_cast<float>( mTexWidth ), .h = static_cast<float>( mTexHeight ) };

    //Default to clip dimensions if clip is given
    if( clip != nullptr )
    {
        dstRect.w = clip->w;
        dstRect.h = clip->h;
    }

    //Resize if new dimensions are given
    if( width > 0 )
    {
        dstRect.w = width;
    }
    if( height > 0 )
    {
        dstRect.h = height;
    }

    SDL_FlipMode flipMode;
    if (flipHorizontal and flipVertical) flipMode = SDL_FLIP_HORIZONTAL_AND_VERTICAL;
    else flipMode = flipHorizontal ? SDL_FLIP_HORIZONTAL : flipVertical ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;

    SDL_FPoint anchor;
    anchor.x = 0;
    anchor.y = 0;

    mDegrees = 0;

    //Render texture
    SDL_RenderTextureRotated(renderer, mTexture, clip, &dstRect, mDegrees, &anchor, flipMode);

    //SDL_Log("X: %f | Y: %f | W: %f | H: %f", dstRect.x, dstRect.y, dstRect.w, dstRect.h);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &dstRect);
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
    mTexture = texture;
    mTexWidth = texture->w;
    mTexHeight = texture->h;
}