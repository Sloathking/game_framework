//
// Created by sloath on 10/26/26.
//

#include "include/Component3D.h"

Component3D::Component3D(Actor3D* owner, const int updateOrder) : Component(owner, updateOrder), mOwner(owner) {}

void Component3D::Update(const float deltaTime)
{
    Component::Update(deltaTime);
}