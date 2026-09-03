//
// Created by sloath on 03-Sep-26.
//

#include "Game.h"
#include <Engine/include/Actor.h>

Game::Game() = default;

Game::~Game() = default;

void Game::LoadData()
{

}

void Game::UnloadData()
{
    // delete actors
    while (!mActors.empty())
        delete mActors.back();

    // destroy textures
    for (const auto& i : mTextures)
        SDL_DestroyTexture(i.second);
}
