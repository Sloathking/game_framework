//
// Created by sloath on 10/16/26.
//

#include "include/Actor3D.h"
#include "include/Component3D.h"

void Actor3D::Update(const float deltaTime)
{
    if (mState == EActive)
    {
        ComputeWorldTransform();

        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);

        ComputeWorldTransform();
    }
}

void Actor3D::ComputeWorldTransform()
{
    if (mRecomputeWorldTransform)
    {
        mRecomputeWorldTransform = false;
        // scale, rotate, translate
        mWorldTransform = Matrix4::CreateScale(mScale);
        mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
        mWorldTransform *= Matrix4::CreateTranslation(mPosition);

        for (const auto comp : mComponents)
            comp->OnUpdateWorldTransform();
    }
}