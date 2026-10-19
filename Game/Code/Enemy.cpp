//
// Created by sloath on 21-Aug-26.
//

#include "Enemy.h"
#include "Game.h"
#include <Engine/include/Tile.h>
#include <Engine/include/Engine.h>
#include <Engine/include/Renderer2D.h>
#include <Engine/include/CircleComponent.h>
#include <Engine/include/NavComponent.h>
#include <Engine/include/SpriteComponent2D.h>

Enemy::Enemy(Game* game) : Actor2D(game)
{
    //game->GetEnemies().emplace_back(this);

    auto renderer = dynamic_cast<Renderer2D*>(game->GetRenderer());
    auto* spriteComp = new SpriteComponent2D(this);
    spriteComp->SetTexture(renderer->GetTexture("Assets/Airplane.png"));
    spriteComp->SetAnchor(SpriteComponent2D::AnchorPoint::CenterCenter);
    spriteComp->SetCenter(SpriteComponent2D::AnchorPoint::CenterCenter);

    // set pos to start tile of curr grid
    // SetPosition(GetGame()->GetGrid()->GetStartTile()->GetPosition());

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