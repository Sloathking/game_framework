//
// Created by sloath on 21-Aug-26.
//

#include "Enemy.h"

#include "Grid.h"
#include "Tile.h"

#include "../../Engine/include/Engine.h"
#include "../../Engine/include/CircleComponent.h"
#include "../../Engine/include/NavComponent.h"
#include "../../Engine/include/SpriteComponent.h"

Enemy::Enemy(Engine* game) : Actor(game)
{
    //game->GetEnemies().emplace_back(this);

    auto* spriteComp = new SpriteComponent(this);
    spriteComp->SetTexture(game->GetTexture("Assets/Airplane.png"));
    spriteComp->SetAnchor(SpriteComponent::AnchorPoint::CenterCenter);
    spriteComp->SetCenter(SpriteComponent::AnchorPoint::CenterCenter);

    // set pos to start tile of curr grid
    //SetPosition(GetGame()->GetGrid()->GetStartTile()->GetPosition());

    // setup nav comp
    auto* navComp = new NavComponent(this);
    navComp->SetForwardSpeed(150.0f);
    //navComp->StartPath(GetGame()->GetGrid()->GetStartTile());

    // set up collision
    mCircleComp = new CircleComponent(this);
    mCircleComp->SetRadius(25.0f);
}

Enemy::~Enemy()
{
    // const auto it = std::find(GetGame()->GetEnemies().begin(), GetGame()->GetEnemies().end(), this);
    // GetGame()->GetEnemies().erase(it);
}

void Enemy::UpdateActor(const float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    // am i near the end tile?
    // Vector2 diff = GetPosition() - GetGame()->GetGrid()->GetEndTile()->GetPosition();
    // if (Math::NearZero(diff.Length(), 10.0f)) SetState(EDead);
}