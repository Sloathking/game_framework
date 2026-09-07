//
// Created by sloath on 06-Aug-26.
//

#include "include/SpriteComponent.h"
#include "include/Shader.h"
#include "include/Actor.h"
#include "include/Engine.h"

SpriteComponent::SpriteComponent(Actor* owner, const int drawOrder) : Component{owner}, mDrawOrder{drawOrder}
{
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
    if (mIsVisible)
    {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        // //Set texture position
        // SDL_FRect dstRect{
        //     .x = mOwner->GetPosition().x + anchorOffsets[mAnchor].x + offset.x,
        //     .y = mOwner->GetPosition().y + anchorOffsets[mAnchor].y + offset.y,
        //     .w = static_cast<float>(mTexWidth) * mOwner->GetScale(),
        //     .h = static_cast<float>(mTexHeight) * mOwner->GetScale()
        // };
        //
        // // calc rotation point
        // const SDL_FPoint* center = GetCenter(dstRect);
        //
        // //Render texture
        // SDL_RenderTextureRotated(renderer, mTexture, nullptr, &dstRect, -Math::ToDegrees(mOwner->GetRotation()), center, spriteFlipMode);
    }
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
}

SDL_FPoint* SpriteComponent::GetCenter(const SDL_FRect& dstRect)
{
    switch (mRotPoint)
    {
    case 0:
        mCenter.x = 0;
        mCenter.y = 0;
        break;
    case 1:
        mCenter.x = dstRect.w * 0.5f;
        mCenter.y = 0;
        break;
    case 2:
        mCenter.x = dstRect.w;
        mCenter.y = 0;
        break;
    case 3:
        mCenter.x = 0;
        mCenter.y = dstRect.h * 0.5f;
        break;
    case 4:
        mCenter.x = dstRect.w * 0.5f;
        mCenter.y = dstRect.h * 0.5f;
        break;
    case 5:
        mCenter.x = dstRect.w;
        mCenter.y = dstRect.h * 0.5f;
        break;
    case 6:
        mCenter.x = 0;
        mCenter.y = dstRect.h;
        break;
    case 7:
        mCenter.x = dstRect.w * 0.5f;
        mCenter.y = dstRect.h;
        break;
    case 8:
        mCenter.x = dstRect.w;
        mCenter.y = dstRect.h;
        break;
    }
    return &mCenter;
}
