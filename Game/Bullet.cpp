//
// Created by sloath on 21-Aug-26.
//

#include "Bullet.h"

#include "../Engine/include/CircleComponent.h"
#include "../Engine/include/Game.h"
#include "../Engine/include/MoveComponent.h"
#include "../Engine/include/SpriteComponent.h"
#include "Enemy.h"

Bullet::Bullet(Game* game) : Actor(game)
{
    auto* spriteComp = new SpriteComponent(this);
    spriteComp->SetTexture(GetGame()->GetTexture("Assets/Projectile.png"));
    spriteComp->SetAnchor(SpriteComponent::AnchorPoint::CenterCenter);
    spriteComp->SetCenter(SpriteComponent::AnchorPoint::CenterCenter);

    auto* moveComp = new MoveComponent(this);
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