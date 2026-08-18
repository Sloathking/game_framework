//
// Created by sloath on 11-Aug-26.
//

#include "Ship.h"

#include "Asteroid.h"
#include "../Engine/include/Game.h"
#include "../Engine/include/Constants.h"
#include "../Engine/include/SpriteComponent.h"
#include "../Engine/include/InputComponent.h"
#include "Laser.h"
#include "../Engine/include/CircleComponent.h"

Ship::Ship(Game* game) : Actor(game)
{
    mShipSprite = new SpriteComponent(this);
    mShipSprite->SetTexture(game->GetTexture("Assets/Ship.png"));
    mShipSprite->SetAnchor(SpriteComponent::AnchorPoint::CenterCenter);
    mShipSprite->SetCenter(SpriteComponent::AnchorPoint::CenterCenter);

    mCollider = new CircleComponent(this);
    mCollider->SetRadius(40.0f);

    mInputComp = new InputComponent(this);
    mInputComp->SetMass(10.0f);
    mInputComp->SetMaxForwardSpeed(300.0f);
    mInputComp->SetMaxAngularSpeed(Math::TwoPi);
    mInputComp->SetForwardKey(SDLK_W);
    mInputComp->SetBackKey(SDLK_S);
    mInputComp->SetClockwiseKey(SDLK_A);
    mInputComp->SetCounterClockwiseKey(SDLK_D);
}

void Ship::UpdateActor(const float deltaTime)
{
    mLaserCooldown -= deltaTime;

    mInvisibleTimer -= deltaTime;
    if (mInvisibleTimer <= 0.0f)
    {
        mShipSprite->SetVisibility(true);
        mInputComp->SetUpdateState(true);
    }

    // check for collision with Collider for each Asteroid in game
    for (const auto* asteroid : GetGame()->GetAsteroids())
    {
        // if we're colliding with an Asteroid
        if (Intersect( *mCollider,*asteroid->GetCircle()))
        {
            mShipSprite->SetVisibility(false);
            mInputComp->SetUpdateState(false);
            mInvisibleTimer = 2.0;

            // move Ship to center of screen, 0 out rotation
            SetPosition(Vector2(windowWidth * 0.5f, windowHeight * 0.5f));
            mInputComp->SetForwardSpeed(0.0f);
            SetRotation(0.0f);
        }
    }
}

void Ship::HandleEvent(const SDL_Event& event)
{
    if (event.key.key == SDLK_SPACE and mLaserCooldown <= 0.0f)
    {
        // create a laser and set its position/rotation to mine
        auto* laser = new Laser(GetGame());
        laser->SetPosition(GetPosition());
        laser->SetRotation(GetRotation());

        // reset laser cooldown (half second)
        mLaserCooldown = 0.5f;
    }
}