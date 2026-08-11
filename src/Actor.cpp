//
// Created by sloath on 06-Aug-26.
//
#include "../include/Actor.h"
#include "../include/Game.h"
#include "../include/Component.h"

Actor::Actor(class Game* game) : mState{ EActive }, mPosition{ Vector2(0.0f, 0.0f) }, mScale{ 1.0f }, mRotation{ 0.0f }, mGame{ game }
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
void Actor::Update(float deltaTime)
{
    if (mState == EActive)
    {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

// updates all the components attached to the actor (not overridable)
void Actor::UpdateComponents(float deltaTime)
{
    for (auto comp : mComponents)
        comp->Update(deltaTime);
}

// any Actor-specific update code (overridable)
void Actor::UpdateActor(float deltaTime)
{

}

// add/remove components
void Actor::AddComponent(Component* component)
{
    // find insertion point in sorted vector
    // (first element with a order higher than me)
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for (; iter != mComponents.end(); iter++)
        if (myOrder < (*iter)->GetUpdateOrder())
            break;

    mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
    auto iter = std::ranges::find(mComponents, component);
    if (iter != mComponents.end())
        mComponents.erase(iter);
}