//
// Created by sloath on 15-Sep-26.
//

#include "PlaneActor.h"
#include "Game.h"
#include <Engine/include/MeshComponent.h>

#include "Engine/include/Renderer.h"

PlaneActor::PlaneActor(Game* game) : Actor(game)
{
    SetScale(10.0f);
    auto* mc = new MeshComponent(this);
    mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Plane.gpmesh"));
}
