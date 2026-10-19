//
// Created by sloath on 03-Sep-26.
//

#include "Game.h"
#include "Asteroid.h"
#include <Engine/include/Engine.h>
#include <Engine/include/Renderer3D.h>
#include <Engine/include/Actor.h>
#include <Engine/include/InputSystem.h>
#include <Engine/include/Random.h>

Game::Game() = default;

Game::~Game() = default;

void Game::ProcessInput()
{
    Engine::ProcessInput();

    //const InputState& state = mInputSystem->GetState();
}

bool Game::ProcessGameEvent(SDL_Event* event)
{
    switch (event->type)
    {
    default:
        return false;
    }
}

void Game::LoadData()
{

}

void Game::UnloadData()
{
    // delete actors
    while (!mActors.empty())
        delete mActors.back();
}
