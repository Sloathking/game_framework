//
// Created by sloath on 10/15/26.
//

#include "include/SpriteComponent2D.h"
#include "include/Engine.h"
#include "include/Renderer2D.h"
#include "include/Actor2D.h"

SpriteComponent2D::SpriteComponent2D(Actor2D* owner, const int drawOrder) : Component{owner}, mDrawOrder{drawOrder}
{
    auto* renderer = dynamic_cast<Renderer2D*>(mOwner->GetGame()->GetRenderer());
    renderer->AddSprite(this);
}

SpriteComponent2D::~SpriteComponent2D()
{
    auto* renderer = dynamic_cast<Renderer2D*>(mOwner->GetGame()->GetRenderer());
    renderer->RemoveSprite(this);
}

void SpriteComponent2D::Draw(SDL_Renderer* renderer, const Vector2 offset)
{
    if (mIsVisible)
    {
        const auto owner = dynamic_cast<Actor2D*>(mOwner);
        const Vector2 pos = owner->GetPosition();
        const SDL_FRect dstRect {
            .x = pos.x + anchorOffsets[mAnchor].x + mOffset.x - offset.x,
            .y = pos.y + anchorOffsets[mAnchor].y + mOffset.y - offset.y,
            .w = static_cast<float>(mTexWidth),
            .h = static_cast<float>(mTexHeight)
        };

        SDL_RenderTextureRotated(
            renderer, mTexture,
            &mClip, &dstRect,
            -Math::ToDegrees(owner->GetRotation()),
            nullptr, //GetCenter(dstRect),
            mSpriteFlipMode
            );
    }
}

void SpriteComponent2D::SetTexture(SDL_Texture* texture)
{
    mTexture = texture;
    mTexWidth = texture->w;
    mTexHeight = texture->h;

    anchorOffsets = {
        { TopLeft, Vector2(0,0) },
        { TopCenter, Vector2(-(mTexWidth * 0.5f),0) },
        { TopRight, Vector2(-mTexWidth,0) },
        { CenterLeft, Vector2(0,-(mTexHeight * 0.5f)) },
        { CenterCenter, Vector2(-(mTexWidth * 0.5f),-(mTexHeight * 0.5f)) },
        { CenterRight, Vector2(-mTexWidth,-(mTexHeight * 0.5f)) },
        { BottomLeft, Vector2(0,-mTexHeight) },
        { BottomCenter, Vector2(-(mTexWidth * 0.5f),-mTexHeight) },
        { BottomRight, Vector2(-mTexWidth,-mTexHeight) },
    };

    mClip = SDL_FRect(0, 0, mTexWidth, mTexHeight);
}

SDL_FPoint* SpriteComponent2D::GetCenter(const SDL_FRect& dstRect)
{
    auto owner = dynamic_cast<Actor2D*>(mOwner);
    switch (mRotPoint)
    {
    case TopLeft:
        mCenter.x = 0;
        mCenter.y = 0;
        break;
    case TopCenter:
        mCenter.x = dstRect.w * 0.5f;
        mCenter.y = 0;
        break;
    case TopRight:
        mCenter.x = dstRect.w;
        mCenter.y = 0;
        break;
    case CenterLeft:
        mCenter.x = 0;
        mCenter.y = dstRect.h * 0.5f;
        break;
    case CenterCenter:
        mCenter.x = dstRect.w * 0.5f;
        mCenter.y = dstRect.h * 0.5f;
        break;
    case CenterRight:
        mCenter.x = dstRect.w;
        mCenter.y = dstRect.h * 0.5f;
        break;
    case BottomLeft:
        mCenter.x = 0;
        mCenter.y = dstRect.h;
        break;
    case BottomCenter:
        mCenter.x = dstRect.w * 0.5f;
        mCenter.y = dstRect.h;
        break;
    case BottomRight:
        mCenter.x = dstRect.w;
        mCenter.y = dstRect.h;
        break;
    }
    return &mCenter;
}
