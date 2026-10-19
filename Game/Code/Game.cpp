//
// Created by sloath on 03-Sep-26.
//

#include "Game.h"
#include "Asteroid.h"
#include "Cam2DActor.h"
#include "Engine/include/Camera2D.h"
#include "Engine/include/Constants.h"
#include <Engine/include/Actor.h>
#include <Engine/include/Actor2D.h>
#include <Engine/include/Engine.h>
#include <Engine/include/InputSystem.h>
#include <Engine/include/Random.h>
#include <Engine/include/Renderer3D.h>

Game::Game() = default;

Game::~Game() = default;

void Game::ProcessInput()
{
    Engine::ProcessInput();

    const InputState& state = mInputSystem->GetState();
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == EPressed)
    {
        asteroidCount++;
        auto* a = new Asteroid(this);
        const Vector2 pos = Random::GetVector(Vector2::Zero, Vector2(1000, 1000));
        a->SetPosition(pos);
        SDL_Log("Asteroid #%i - X: %f | Y: %f", asteroidCount, pos.x, pos.y);
    }
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
    mCamActor = new Cam2DActor(this);
    mCamActor->SetPosition(Vector2(windowWidth * 0.5f, windowHeight * 0.5f));
}

void Game::UnloadData()
{
    // delete actors
    while (!mActors.empty())
        delete mActors.back();
}
