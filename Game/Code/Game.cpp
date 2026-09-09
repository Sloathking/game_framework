//
// Created by sloath on 03-Sep-26.
//

#include "Game.h"
#include <Engine/include/Actor2D.h>
#include <Engine/include/InputSystem.h>
#include <Engine/include/SpriteComponent.h>
#include <Engine/include/Random.h>

#include "Engine/include/Texture.h"


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
    for (int i = 0; i < 20; ++i)
    {
        auto tempAct = new Actor2D(this);

        tempAct->SetPosition(Random::GetVector(-1 * mWorldSize * 0.5 ,mWorldSize * 0.5));
        auto* sprite = new SpriteComponent(tempAct);
        auto* tex = new Texture();
        tex->Load("Assets/Asteroid.png");
        sprite->SetTexture(tex);

        mSpriteActors.emplace_back(tempAct);
    }
}

void Game::UnloadData()
{
    // delete actors
    while (!mActors.empty())
        delete mActors.back();

    // destroy textures
    for (const auto& i : mTextures)
        i.second->Unload();
}
