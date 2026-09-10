//
// Created by sloath on 10-Sep-26.
//

#include "include/Actor3D.h"
#include "include/Component.h"

Actor3D::Actor3D(Engine* game) : Actor(game)
{

}

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

void Actor3D::UpdateActor(float deltaTime)
{

}

void Actor3D::ActorInput(const InputState& state)
{

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
