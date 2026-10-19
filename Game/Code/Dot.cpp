//
// Created by sloath on 27-Aug-26.
//

#include "Dot.h"
#include "Game.h"
#include <Engine/include/Renderer2D.h>
#include <Engine/include/SpriteComponent2D.h>
#include <Engine/include/CameraComponent.h>
#include <Engine/include/InputSystem.h>

Dot::Dot(Game* game) : Actor2D(game)
{
    auto* renderer = dynamic_cast<Renderer2D*>(GetGame()->GetRenderer());

    auto* sprite = new SpriteComponent2D(this);
    sprite->SetTexture(renderer->GetTexture("Assets/Projectile.png"));
    sprite->SetAnchor(SpriteComponent2D::CenterCenter);
    sprite->SetCenter(SpriteComponent2D::CenterCenter);

    // mCameraComp = new CameraComponent(this);
    //game->SetMainCamera(mCameraComp);
}

void Dot::UpdateActor(float deltaTime)
{

}

void Dot::ActorInput(const InputState& state)
{
    Vector2 pos = GetPosition();
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_W) == EHeld) pos.y -= 10.0;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_S) == EHeld) pos.y += 10.0;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_D) == EHeld) pos.x += 10.0;
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_A) == EHeld) pos.x -= 10.0;
    SetPosition(pos);
}