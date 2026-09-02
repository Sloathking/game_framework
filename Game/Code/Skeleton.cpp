//
// Created by sloath on 11-Aug-26.
//

#include "Skeleton.h"
#include "../../Engine/include/Game.h"
#include "../../Engine/include/AnimSpriteComponent.h"
#include "../../Engine/include/Constants.h"

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
}

void Skeleton::ActorInput(const InputState& state)
{

}
