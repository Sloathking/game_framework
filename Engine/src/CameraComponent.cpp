//
// Created by sloath on 27-Aug-26.
//

#include "include/CameraComponent.h"
#include "include/Actor.h"
#include "include/Engine.h"
#include "include/Renderer.h"

CameraComponent::CameraComponent(Actor* owner, const int updateOrder) : Component(owner, updateOrder)
{

}

void CameraComponent::SetViewMatrix(const Matrix4& view) const
{
    const Engine* game = mOwner->GetGame();
    game->GetRenderer()->SetViewMatrix(view);
}
