//
// Created by sloath on 21-Aug-26.
//

#include "Bullet.h"
#include "Enemy.h"
#include "Game.h"
#include <Engine/include/Renderer2D.h>
#include <Engine/include/SpriteComponent2D.h>
#include <Engine/include/MoveComponent2D.h>
#include <Engine/include/CircleComponent.h>

Bullet::Bullet(Game* game) : Actor2D(game)
{
    const auto renderer = dynamic_cast<Renderer2D*>(game->GetRenderer());

    auto* spriteComp = new SpriteComponent2D(this);
    spriteComp->SetTexture(renderer->GetTexture("Assets/Projectile.png"));
    spriteComp->SetAnchor(SpriteComponent2D::AnchorPoint::CenterCenter);
    spriteComp->SetCenter(SpriteComponent2D::AnchorPoint::CenterCenter);

    auto* moveComp = new MoveComponent2D(this);
    moveComp->SetForwardSpeed(400.0f);

    mCircleComp = new CircleComponent(this);
    mCircleComp->SetRadius(5.0f);

    mLiveTime = 1.0f;
}

void Bullet::UpdateActor(const float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    /*
    // check for collision vs enemies
    for (Enemy* e : GetGame()->GetEnemies())
    {
        if (Intersect(*mCircleComp, *e->GetCircle()))
        {
            // both die
            e->SetState(EDead);
            SetState(EDead);
            break;
        }
    }
    */

    mLiveTime -= deltaTime;
    if (mLiveTime <= 0.0f) SetState(EDead);
}