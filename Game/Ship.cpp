//
// Created by sloath on 11-Aug-26.
//

#include "Ship.h"
#include "../Engine/include/Game.h"
#include "../Engine/include/Constants.h"
#include "../Engine/include/SpriteComponent.h"
#include "../Engine/include/InputComponent.h"

Ship::Ship(Game* game) : Actor(game)
{
    mShipSprite = new SpriteComponent(this);
    mShipSprite->SetTexture(game->GetTexture("Assets/Ship.png"));
    mShipSprite->SetAnchor(SpriteComponent::AnchorPoint::CenterCenter);
    mShipSprite->SetCenter(SpriteComponent::AnchorPoint::CenterCenter);

    auto* inputComp = new InputComponent(this);
    inputComp->SetMaxForwardSpeed(300.0f);
    inputComp->SetMaxAngularSpeed(Math::TwoPi);
    inputComp->SetForwardKey(SDLK_W);
    inputComp->SetBackKey(SDLK_S);
    inputComp->SetClockwiseKey(SDLK_A);
    inputComp->SetCounterClockwiseKey(SDLK_D);
}

void Ship::UpdateActor(const float deltaTime)
{
    Actor::UpdateActor(deltaTime);
}

void Ship::HandleEvent(const SDL_Event& event)
{

}