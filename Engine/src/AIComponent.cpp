//
// Created by sloath on 19-Aug-26.
//

#include "../include/AIComponent.h"

#include "../include/AIState.h"
#include "SDL3/SDL_log.h"

AIComponent::AIComponent(Actor* owner) : Component(owner)
{

}

void AIComponent::Update(const float deltaTime)
{
    if (mCurrState)
        mCurrState->Update(deltaTime);
}

void AIComponent::ChangeState(const std::string& name)
{
    if (mCurrState) mCurrState->OnExit();

    if (const auto it = mStateMap.find(name); it != mStateMap.end())
    {
        mCurrState = it->second;
        mCurrState->OnEnter();
    }
    else
    {
        SDL_Log("Unable to find State '%s' in State Map", name.c_str());
        mCurrState = nullptr;
    }
}

void AIComponent::RegisterState(AIState* state)
{
    mStateMap.emplace(state->GetName(), state);
}