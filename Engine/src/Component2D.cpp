//
// Created by sloath on 10/26/26.
//

#include "include/Component2D.h"

Component2D::Component2D(Actor2D* owner, const int updateOrder) : Component(owner, updateOrder), mOwner(owner) {}

void Component2D::Update(const float deltaTime)
{
    Component::Update(deltaTime);
}