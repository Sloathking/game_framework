//
// Created by sloath on 27-Aug-26.
//

#include "include/CameraComponent.h"
#include "include/Actor3D.h"
#include "include/Engine.h"
#include "include/Renderer3D.h"

CameraComponent::CameraComponent(Actor3D* owner, const int updateOrder) : Component3D(owner, updateOrder)
{

}

void CameraComponent::SetViewMatrix(const Matrix4& view) const
{
    const Engine* game = mOwner->GetGame();
    auto* renderer = dynamic_cast<Renderer3D*>(game->GetRenderer());
    renderer->SetViewMatrix(view);
}
