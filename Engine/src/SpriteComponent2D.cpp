//
// Created by sloath on 10/15/26.
//

#include "include/SpriteComponent2D.h"
#include "include/Engine.h"
#include "include/Renderer2D.h"
#include "include/Actor.h"
#include "include/Shader.h"
#include "include/Texture.h"

SpriteComponent2D::SpriteComponent2D(Actor* owner, const int drawOrder) : Component{owner}, mDrawOrder{drawOrder}
{
    auto* renderer = dynamic_cast<Renderer2D*>(mOwner->GetGame()->GetRenderer());
    renderer->AddSprite(this);
}

SpriteComponent2D::~SpriteComponent2D()
{
    auto* renderer = dynamic_cast<Renderer2D*>(mOwner->GetGame()->GetRenderer());
    renderer->RemoveSprite(this);
}

void SpriteComponent2D::Draw(Shader* shader)
{
    if (mIsVisible)
    {
        // // scale the quad by the width/height of texture
        // const Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.0f);
        // const Matrix4 world = scaleMat * mOwner->GetWorldTransform();
        //
        // // set world transform
        // shader->SetMatrixUniform("uWorldTransform", world);
        //
        // mTexture->SetActive();
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}

void SpriteComponent2D::SetTexture(SDL_Texture* texture)
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

SDL_FPoint* SpriteComponent2D::GetCenter(const SDL_FRect& dstRect)
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
