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

void SpriteComponent::Draw(SDL_Renderer* renderer, const SDL_FRect* clip, const float width, const float height)
{
    /*SDL_Log("dstRect.x: %f", mOwner->GetPosition().x + anchorOffsets[mAnchor].x + mXOffset);
    SDL_Log("dstRect.y: %f", mOwner->GetPosition().y + anchorOffsets[mAnchor].y + mYOffset);*/
    //Set texture position
    SDL_FRect dstRect{ .x = mOwner->GetPosition().x + anchorOffsets[mAnchor].x + mXOffset, .y = mOwner->GetPosition().y + anchorOffsets[mAnchor].y + mYOffset,
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
    anchor.x = rotOffsets[mRotPoint].x;
    anchor.y = rotOffsets[mRotPoint].y;

    //Render texture
    SDL_RenderTextureRotated(renderer, mTexture, clip, &dstRect, mDegrees, &anchor, flipMode);
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
    mTexture = texture;
    mTexWidth = texture->w;
    mTexHeight = texture->h;

    anchorOffsets = {
        { TopLeft, Vector2(0,0) },{ TopCenter, Vector2(-(mTexWidth * 0.5f),0) }, { TopRight, Vector2(-mTexWidth,0) },
        { CenterLeft, Vector2(0,-(mTexHeight * 0.5f)) },{ CenterCenter, Vector2(-(mTexWidth * 0.5f),-(mTexHeight * 0.5f)) }, { CenterRight, Vector2(-mTexWidth,-(mTexHeight * 0.5f)) },
        { BottomLeft, Vector2(0,-mTexHeight) },{ BottomCenter, Vector2(-(mTexWidth * 0.5f),-mTexHeight) }, { BottomRight, Vector2(-mTexWidth,-mTexHeight) },
    };

    rotOffsets = {
        { TopLeft, Vector2(0,0) },{ TopCenter, Vector2(mTexWidth * 0.5f,0) }, { TopRight, Vector2(mTexWidth,0) },
        { CenterLeft, Vector2(0,mTexHeight * 0.5f) },{ CenterCenter, Vector2(mTexWidth * 0.5f,mTexHeight * 0.5f) }, { CenterRight, Vector2(mTexWidth,mTexHeight * 0.5f) },
        { BottomLeft, Vector2(0,mTexHeight) },{ BottomCenter, Vector2(mTexWidth * 0.5f,mTexHeight) }, { BottomRight, Vector2(mTexWidth,mTexHeight) },
    };
}