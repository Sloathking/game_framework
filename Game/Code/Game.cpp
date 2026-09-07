//
// Created by sloath on 03-Sep-26.
//

#include "Game.h"
#include <Engine/include/Actor.h>
#include <Engine/include/InputSystem.h>
#include <Engine/include/VertexArray.h>


Game::Game() = default;

Game::~Game() = default;

void Game::ProcessInput()
{
    Engine::ProcessInput();
    const InputState state = mInputSystem->GetState();
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == EPressed)
    {
        SDL_Log("Left Arrow");
    }
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == EPressed)
    {
        SDL_Log("Right Arrow");
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

    // destroy textures
    for (const auto& i : mTextures)
        SDL_DestroyTexture(i.second);
}
