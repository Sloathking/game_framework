//
// Created by sloath on 03-Sep-26.
//

#include "Game.h"
#include "Cam2DActor.h"
#include "PauseScreen.h"
#include "HexGridActor.h"
#include <Engine/include/Engine.h>
#include <Engine/include/Constants.h>
#include <Engine/include/Actor2D.h>
#include <Engine/include/Renderer2D.h>
#include <Engine/include/InputSystem.h>
#include <Engine/include/Random.h>

Game::Game()
{
    const std::string basePath = SDL_GetBasePath();
    std::string gamePath = basePath;
    int count = 3;
    for (int i = static_cast<int>(gamePath.length()) - 1; i >= 0; --i)
    {
        if (count == 0) break;
        if (gamePath[i] == '/' and count != 0)
        {
            gamePath.erase(gamePath.begin() + i, gamePath.end());
            count--;
        }
    }
    gamePath += "/Game/";
    GamePath = gamePath;
}

Game::~Game() = default;

void Game::ProcessInput()
{
    Engine::ProcessInput();

    const InputState& state = mInputSystem->GetState();
    if (mGameState == EGameplay)
    {
        if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == EPressed)
            new PauseScreen(this);
        if (state.Mouse.GetButtonState(MouseState::Left) == EPressed)
        {
            // convert mouse position Screen Space -> World Space
            const auto renderScale = static_cast<Renderer2D*>(mRenderer)->GetRenderScale();
            const Vector2 camOffset = mCamActor->GetCamOffset(renderScale);
            Vector2 mousePos = state.Mouse.GetPosition();
            mousePos.x = mousePos.x / renderScale + camOffset.x;
            mousePos.y = mousePos.y / renderScale + camOffset.y;
            auto hex = mHexGrid->GetHex(mousePos);
        }
    }
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_MINUS) == EPressed)
    {
        const auto renderer = static_cast<Renderer2D*>(mRenderer);
        const float uiScale = renderer->GetUIRenderScale();
        SDL_Log("uiScale: %f", uiScale);
        renderer->SetUIRenderScale(uiScale - 0.01f);
    }
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_EQUALS) == EPressed)
    {
        const auto renderer = static_cast<Renderer2D*>(mRenderer);
        const float uiScale = renderer->GetUIRenderScale();
        SDL_Log("uiScale: %f", uiScale);
        renderer->SetUIRenderScale(uiScale + 0.01f);
    }
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_R) == EPressed)
    {
        mHexGrid->GenerateGrid(mRows, mCols);
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
    mCamActor->SetPosition(Vector2(0, 0));
    mCamActor->SetPosition(Vector2(100 * 100, 100 * 100));

    mHexGrid = new HexGridActor(this);
    mHexGrid->SetPosition(Vector2(0, 0));
    mHexGrid->GenerateGrid(mRows, mCols);
}

void Game::UnloadData()
{
    Engine::UnloadData();
    mCamActor = nullptr;
    mHexGrid = nullptr;
}