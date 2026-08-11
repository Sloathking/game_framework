//
// Created by sloath on 11-Aug-26.
//

#include "Skeleton.h"
#include "../Engine/include/Game.h"
#include "../Engine/include/AnimSpriteComponent.h"

Skeleton::Skeleton(Game* game) : Actor(game)
{
    mAnimSprite = new AnimSpriteComponent(this);
    mAnimSprite->SetAnimFPS(12.0f);
    std::vector<SDL_Texture*> anims{};

    anims.clear();
    anims.emplace_back(game->GetTexture("Assets/Character01.png"));
    mAnimSprite->AddAnimation(static_cast<int>(DEFAULT), anims);

    anims.clear();
    const std::string fileNameStart = "Assets/Character0";
    for (int i = 1; i <= 6; ++i)
        anims.emplace_back(game->GetTexture(fileNameStart + std::to_string(i) + ".png"));
    mAnimSprite->AddAnimation(static_cast<int>(WALKING), anims);

    mAnimSprite->PlayAnimation(static_cast<int>(WALKING));
}

void Skeleton::UpdateActor(float deltaTime)
{

}

void Skeleton::HandleEvent(const SDL_Event& event)
{

}