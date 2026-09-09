//
// Created by sloath on 09-Sep-26.
//

#include "include/Actor2D.h"
#include "include/Component.h"

Actor2D::Actor2D(Engine* game) : Actor(game)
{

}

void Actor2D::Update(const float deltaTime)
{
    if (mState == EActive)
    {
        ComputeWorldTransform();

        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);

        ComputeWorldTransform();
    }
}

void Actor2D::UpdateActor(float deltaTime)
{

}

void Actor2D::ActorInput(const InputState& state)
{

}

void Actor2D::ComputeWorldTransform()
{
    if (mRecomputeWorldTransform)
    {
        mRecomputeWorldTransform = false;
        // scale, rotation, transform
        mWorldTransform = Matrix4::CreateScale(mScale);
        mWorldTransform *= Matrix4::CreateRotationZ(mRotation);
        mWorldTransform *= Matrix4::CreateTranslation(Vector3(mPosition.x, mPosition.y, 0.0f));

        for (const auto comp : mComponents)
            comp->OnUpdateWorldTransform();
    }
}