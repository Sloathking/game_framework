//
// Created by sloath on 06-Aug-26.
//
#include "../include/Component.h"
#include "../include/Actor.h"

Component::Component(Actor* owner, const int updateOrder) : mOwner{ owner }, mUpdateOrder{ updateOrder }
{
    mOwner->AddComponent(this);
}

// destructor
Component::~Component()
{
    mOwner->RemoveComponent(this);
}

// update this component by delta time
void Component::Update(float deltaTime)
{

}