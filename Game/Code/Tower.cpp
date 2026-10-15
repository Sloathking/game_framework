//
// Created by sloath on 21-Aug-26.
//

#include "Tower.h"
#include "Game.h"
#include "Enemy.h"
#include <Engine/include/Renderer2D.h>
#include <Engine/include/MoveComponent.h>
#include <Engine/include/SpriteComponent2D.h>

Tower::Tower(Game* game) : Actor(game)
{
    auto* renderer = dynamic_cast<Renderer2D*>(GetGame()->GetRenderer());
    auto* spriteComp = new SpriteComponent2D(this);
    spriteComp->SetTexture(renderer->GetTexture("Assets/Tower.png"));
    spriteComp->SetAnchor(SpriteComponent2D::AnchorPoint::CenterCenter);
    spriteComp->SetCenter(SpriteComponent2D::AnchorPoint::CenterCenter);

    mMoveComp = new MoveComponent(this);

    mNextAttack = AttackTime;
}

void Tower::UpdateActor(const float deltaTime)
{
    Actor::UpdateActor(deltaTime);
    mNextAttack -= deltaTime;
    /*if (mNextAttack <= 0.0f)
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
    }*/
}