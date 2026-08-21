//
// Created by sloath on 21-Aug-26.
//

#include "Tower.h"

#include "../Engine/include/Game.h"
#include "../Engine/include/MoveComponent.h"
#include "../Engine/include/SpriteComponent.h"
#include "Enemy.h"
#include "Bullet.h"

Tower::Tower(Game* game) : Actor(game)
{
    auto* spriteComp = new SpriteComponent(this);
    spriteComp->SetTexture(GetGame()->GetTexture("Assets/Tower.png"));
    spriteComp->SetAnchor(SpriteComponent::AnchorPoint::CenterCenter);
    spriteComp->SetCenter(SpriteComponent::AnchorPoint::CenterCenter);

    mMoveComp = new MoveComponent(this);

    mNextAttack = AttackTime;
}

void Tower::UpdateActor(const float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    mNextAttack -= deltaTime;
    if (mNextAttack <= 0.0f)
    {
        if (const Enemy* enemy = GetGame()->GetNearestEnemy(GetPosition()))
        {
            const Vector2 dir = enemy->GetPosition() - GetPosition();
            if (const float dist = dir.Length(); dist < AttackRange)
            {
                // face enemy
                SetRotation(Math::Atan2(-dir.y, dir.x));
                // spawn bullet at tower position facing enemy
                auto* b = new Bullet(GetGame());
                b->SetPosition(GetPosition());
                b->SetRotation(GetRotation());
            }
        }
        mNextAttack += AttackTime;
    }
}