//
// Created by sloath on 06-Aug-26.
//

#include "include/SpriteComponent3D.h"
#include "include/Engine.h"
#include "include/Renderer3D.h"
#include "include/Actor3D.h"
#include "include/Shader.h"
#include "include/Texture.h"

SpriteComponent3D::SpriteComponent3D(Actor3D* owner, const int drawOrder) : Component{owner}, mDrawOrder{drawOrder}
{
    auto* renderer = dynamic_cast<Renderer3D*>(owner->GetGame()->GetRenderer());
    renderer->AddSprite(this);
}

SpriteComponent3D::~SpriteComponent3D()
{
    auto* renderer = dynamic_cast<Renderer3D*>(mOwner->GetGame()->GetRenderer());
    renderer->RemoveSprite(this);
}

void SpriteComponent3D::Draw(Shader* shader)
{
    if (mIsVisible)
    {
        // scale the quad by the width/height of texture
        const Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.0f);
        const Matrix4 world = scaleMat * dynamic_cast<Actor3D*>(mOwner)->GetWorldTransform();

        // set world transform
        shader->SetMatrixUniform("uWorldTransform", world);

        mTexture->SetActive();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}

void SpriteComponent3D::SetTexture(Texture* texture)
{
    mTexture = texture;
    mTexWidth = texture->GetWidth();
    mTexHeight = texture->GetHeight();
}
