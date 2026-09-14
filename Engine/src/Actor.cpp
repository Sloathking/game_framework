//
// Created by sloath on 06-Aug-26.
//

#include "include/Actor.h"
#include "include/Engine.h"
#include "include/Component.h"
#include <algorithm>

Actor::Actor(Engine* game) : mGame{ game }
{
    mGame->AddActor(this);
}

Actor::~Actor()
{
    mGame->RemoveActor(this);

    while (!mComponents.empty())
        delete mComponents.back();
}

void Actor::Update(const float deltaTime)
{
    if (mState == EActive)
    {
        ComputeWorldTransform();

        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);

        ComputeWorldTransform();
    }
}


void Actor::UpdateComponents(const float deltaTime) const
{
    for (const auto comp : mComponents)
        comp->Update(deltaTime);
}

void Actor::UpdateActor(float deltaTime)
{

}

void Actor::ProcessInput(const InputState& state)
{
    if (mState == EActive)
    {
        for (const auto comp : mComponents)
            comp->ProcessInput(state);
        ActorInput(state);
    }
}

void Actor::ActorInput(const InputState& state)
{

}

void Actor::AddComponent(Component* component)
{
    // find insertion point in sorted vector (first element with a order higher than me)
    const int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for (; iter != mComponents.end(); ++iter)
        if (myOrder < (*iter)->GetUpdateOrder())
            break;

    mComponents.insert(iter, component);
}

void Actor::RemoveComponent(const Component* component)
{
    if (const auto iter = std::find(mComponents.begin(), mComponents.end(), component); iter != mComponents.end())
        mComponents.erase(iter);
}

void Actor::ComputeWorldTransform()
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