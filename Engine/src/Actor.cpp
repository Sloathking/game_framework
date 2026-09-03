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

// update function called from Game (not overridable)
void Actor::Update(const float deltaTime)
{
    if (mState == EActive)
    {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

// updates all the components attached to the actor (not overridable)
void Actor::UpdateComponents(const float deltaTime) const
{
    for (const auto comp : mComponents)
        comp->Update(deltaTime);
}

// any Actor-specific update code (overridable)
void Actor::UpdateActor(const float deltaTime)
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