//
// Created by sloath on 10/15/26.
//

#include "include/SpriteComponent2D.h"
#include "include/Engine.h"
#include "include/Renderer2D.h"
#include "include/Actor2D.h"

SpriteComponent2D::SpriteComponent2D(Actor2D* owner, const int drawOrder) : Component2D{owner}, mDrawOrder{drawOrder}
{
    auto* renderer = dynamic_cast<Renderer2D*>(mOwner->GetGame()->GetRenderer());
    renderer->AddSprite(this);
}

SpriteComponent2D::~SpriteComponent2D()
{
    auto* renderer = dynamic_cast<Renderer2D*>(mOwner->GetGame()->GetRenderer());
    renderer->RemoveSprite(this);
}

void SpriteComponent2D::Draw(SDL_Renderer* renderer, const Vector2 offset, const float scaleFactor)
{
    if (mIsVisible)
    {
        const auto owner = (mOwner);
        const Vector2 pos = owner->GetPosition();
        const SDL_FRect dstRect {
            .x = (pos.x + mOffset.x - offset.x) * scaleFactor,
            .y = (pos.y + mOffset.y - offset.y) * scaleFactor,
            .w = static_cast<float>(mTexWidth) * owner->GetScale() * scaleFactor,
            .h = static_cast<float>(mTexHeight) * owner->GetScale() * scaleFactor
        };

        SDL_RenderTextureRotated(
            renderer, mTexture,
            &mClip, &dstRect,
            -Math::ToDegrees(owner->GetRotation()),
            nullptr,
            mSpriteFlipMode
            );
    }
}

void SpriteComponent2D::SetTexture(SDL_Texture* texture)
{
    mTexture = texture;
    mTexWidth = texture->w;
    mTexHeight = texture->h;

    mClip = SDL_FRect(0, 0, mTexWidth, mTexHeight);
}
