//
// Created by sloath on 06-Aug-26.
//

#include "include/SpriteComponent.h"
#include "include/Engine.h"
#include "include/Actor2D.h"
#include "include/Shader.h"
#include "include/Texture.h"

SpriteComponent::SpriteComponent(Actor2D* owner, const int drawOrder) : Component{owner}, mDrawOrder{drawOrder}
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
        // scale the quad by the width/height of texture
        const Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.0f);
        //const Matrix4 scaleMat = Matrix4::CreateScale(100.0f, 100.0f, 1.0f);
        const Matrix4 world = scaleMat * mOwner->GetWorldTransform();

        // set world transform
        shader->SetMatrixUniform("uWorldTransform", world);

        mTexture->SetActive();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}

void SpriteComponent::SetTexture(Texture* texture)
{
    mTexture = texture;
    mTexWidth = texture->GetWidth();
    mTexHeight = texture->GetHeight();

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
