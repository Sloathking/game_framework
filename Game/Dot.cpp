//
// Created by sloath on 27-Aug-26.
//

#include "Dot.h"

#include "../Engine/include/Game.h"
#include "../Engine/include/SpriteComponent.h"
#include "../Engine/include/InputSystem.h"

Dot::Dot(Game* game) : Actor(game)
{
    auto* sprite = new SpriteComponent(this);
    sprite->SetTexture(game->GetTexture("Assets/Projectile.png"));
    sprite->SetAnchor(SpriteComponent::CenterCenter);
    sprite->SetCenter(SpriteComponent::CenterCenter);
    SetRotation(Math::ToRadians(270.0f));
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