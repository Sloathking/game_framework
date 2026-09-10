//
// Created by sloath on 03-Sep-26.
//

#include "Game.h"
#include "Ship.h"
#include <Engine/include/Actor2D.h>
#include <Engine/include/InputSystem.h>
#include <Engine/include/Texture.h>
#include <Engine/include/SpriteComponent.h>
#include <Engine/include/Mesh.h>
#include <Engine/include/Random.h>

Game::Game() = default;

Game::~Game() = default;

void Game::ProcessInput()
{
    Engine::ProcessInput();
}

void Game::LoadData()
{
    mMesh = GetMesh("Assets/Cube.gpmesh");
}

void Game::UnloadData()
{
    // delete actors
    while (!mActors.empty())
        delete mActors.back();

    // destroy textures
    for (const auto& tex : mTextures)
        tex.second->Unload();

    // destroy meshes
    for (const auto& mesh : mMeshes)
        mesh.second->Unload();

}
