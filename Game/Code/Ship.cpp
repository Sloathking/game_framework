//
// Created by sloath on 11-Aug-26.
//

#include "Ship.h"
#include "Asteroid.h"
#include "Laser.h"
#include <Engine/include/Engine.h>
#include <Engine/include/Renderer2D.h>
#include <Engine/include/SpriteComponent2D.h>
#include <Engine/include/InputSystem.h>
#include <Engine/include/CircleComponent.h>

Ship::Ship(Engine* game) : Actor(game)
{
    auto* renderer = dynamic_cast<Renderer2D*>(GetGame()->GetRenderer());
    mShipSprite = new SpriteComponent2D(this);
    mShipSprite->SetTexture(renderer->GetTexture("Assets/Ship.png"));

    // mShipSprite->SetAnchor(SpriteComponent::AnchorPoint::CenterCenter);
    // mShipSprite->SetCenter(SpriteComponent::AnchorPoint::CenterCenter);

    mCollider = new CircleComponent(this);
    mCollider->SetRadius(40.0f);
}

void Ship::UpdateActor(const float deltaTime)
{
    if (mLaserCooldown >= 0.0)
        mLaserCooldown -= deltaTime;

    mInvisibleTimer -= deltaTime;
    if (mInvisibleTimer <= 0.0f)
    {
        mShipSprite->SetVisibility(true);
    }
}

void Ship::ActorInput(const InputState& state)
{
    // if (state.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) and mLaserCooldown <= 0.0f)
    // {
    //     // create a laser and set its position/rotation to mine
    //     auto* laser = new Laser(GetGame(), GetForward());
    //     laser->SetPosition(GetPosition());
    //     laser->SetRotation(GetRotation());
    //
    //     // reset laser cooldown (half second)
    //     mLaserCooldown = 0.5f;
    // }
}