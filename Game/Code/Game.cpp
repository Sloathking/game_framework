//
// Created by sloath on 03-Sep-26.
//

#include "Game.h"
#include "Cam2DActor.h"
#include "PauseScreen.h"
#include "HexGridActor.h"
#include <Engine/include/Engine.h>
#include <Engine/include/Actor2D.h>
#include <Engine/include/Renderer2D.h>
#include <Engine/include/InputSystem.h>

Game::Game() = default;

Game::~Game() = default;

void Game::ProcessInput()
{
    Engine::ProcessInput();

    const InputState& state = mInputSystem->GetState();
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == EPressed)
        new PauseScreen(this);
    if (state.Mouse.GetButtonState(MouseState::Left) == EPressed)
    {
        // convert mouse position Screen Space -> World Space
        const auto renderScale = static_cast<Renderer2D*>(mRenderer)->GetRenderScale();
        const Vector2 camOffset = mCamActor->GetCamOffset(renderScale);
        Vector2 mousePos = state.Mouse.GetPosition();
        mousePos.x /= renderScale;
        mousePos.y /= renderScale;
        mousePos += camOffset;
        const Vector2 hexPos{mousePos.x / 256.f, mousePos.y / (256.f * 0.75f)};
        SDL_Log("X: %d | Y: %d", static_cast<int>(hexPos.x), static_cast<int>(hexPos.y));
        // auto hex = mHexGrid->GetHex(static_cast<int>(hexPos.x), static_cast<int>(hexPos.y));
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

    mHexGrid = new HexGridActor(this);
    mHexGrid->SetPosition(Vector2(0, 0));
    mHexGrid->GenerateGrid(75, 50);
}

void Game::UnloadData()
{
    Engine::UnloadData();
}