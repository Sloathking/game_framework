//
// Created by sloath on 11-Aug-26.
//

#include "Ship.h"
#include "../Engine/include/Game.h"
#include "../Engine/include/AnimSpriteComponent.h"
#include "../Engine/include/Constants.h"
#include <SDL3/SDL.h>

Ship::Ship(Game* game) : Actor(game)
{
    const auto animSprite{ new AnimSpriteComponent(this) };
    const std::vector<SDL_Texture*> anims{
        game->GetTexture("Assets/Ship01.png"),
        game->GetTexture("Assets/Ship02.png"),
        game->GetTexture("Assets/Ship03.png"),
        game->GetTexture("Assets/Ship04.png"),
    };
    animSprite->AddAnimation(0, AnimSpriteComponent::LOOP, anims);
    animSprite->PlayAnimation(0);
}

void Ship::UpdateActor(const float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    // update pos based on speeds and delta time
    Vector2 pos = GetPosition();
    pos.x += mRightSpeed * deltaTime;
    pos.y += mDownSpeed * deltaTime;

    // restrict pos to left half of screen
    if (pos.x < 0) pos.x = 0;
    else if (pos.x > windowWidth) pos.x = windowWidth;

    if (pos.y < 0) pos.y = 0;
    else if (pos.y > windowHeight) pos.y = windowHeight;

    SetPosition(pos);
}

void Ship::HandleEvent(const SDL_Event& event)
{
    mRightSpeed = 0.0f;
    mDownSpeed = 0.0f;

    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        switch (event.key.key)
        {
        case SDLK_W: mDownSpeed -= 300.0f; break;
        case SDLK_S: mDownSpeed += 300.0f; break;
        case SDLK_A: mRightSpeed -= 300.0f; break;
        case SDLK_D: mRightSpeed += 300.0f; break;
        default: break;
        }
    }
}