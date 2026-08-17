//
// Created by sloath on 11-Aug-26.
//

#include "Skeleton.h"
#include "../Engine/include/Game.h"
#include "../Engine/include/AnimSpriteComponent.h"
#include "../Engine/include/Constants.h"

Skeleton::Skeleton(Game* game) : Actor(game)
{
    mAnimSprite = new AnimSpriteComponent(this);
    mAnimSprite->SetAnimFPS(12.0f);
    std::vector<SDL_Texture*> anims{};

    anims.clear();
    anims.emplace_back(game->GetTexture("Assets/Character01.png"));
    mAnimSprite->AddAnimation(DEFAULT, AnimSpriteComponent::LOOP, anims);

    anims.clear();
    std::string fileNameStart = "Assets/Character0";
    for (int i = 1; i <= 6; ++i)
        anims.emplace_back(game->GetTexture(fileNameStart + std::to_string(i) + ".png"));
    mAnimSprite->AddAnimation(WALKING, AnimSpriteComponent::LOOP, anims);

    anims.clear();
    for (int i = 7; i <= 9; i++)
        anims.emplace_back(game->GetTexture(fileNameStart + std::to_string(i) + ".png"));
    fileNameStart = "Assets/Character";
    for (int i = 10; i <= 15; i++)
        anims.emplace_back(game->GetTexture(fileNameStart + std::to_string(i) + ".png"));
    mAnimSprite->AddAnimation(JUMPING, AnimSpriteComponent::NO_LOOP, anims);

    anims.clear();
    for (int i = 16; i <= 18; i++)
        anims.emplace_back(game->GetTexture(fileNameStart + std::to_string(i) + ".png"));
    mAnimSprite->AddAnimation(PUNCH, AnimSpriteComponent::NO_LOOP, anims);

    mAnimSprite->PlayAnimation(DEFAULT);
}

void Skeleton::UpdateActor(const float deltaTime)
{
    Actor::UpdateActor(deltaTime);

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

void Skeleton::HandleEvent(const SDL_Event& event)
{
    mRightSpeed = 0.0f;
    mDownSpeed = 0.0f;

    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        switch (event.key.key)
        {
        case SDLK_W:
            mDownSpeed -= 300.0f;
            if (mAnimSprite->GetCurrAnim() != WALKING) mAnimSprite->PlayAnimation(WALKING);
            break;
        case SDLK_S:mDownSpeed += 300.0f; break;
        case SDLK_A: mRightSpeed -= 300.0f; break;
        case SDLK_D: mRightSpeed += 300.0f; break;
        case SDLK_SPACE:
            mAnimSprite->PlayAnimation(JUMPING);
            break;
        case SDLK_V:
            mAnimSprite->PlayAnimation(PUNCH);
            break;
        default:
            break;
        }
    }
}
