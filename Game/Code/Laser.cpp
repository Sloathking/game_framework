//
// Created by sloath on 18-Aug-26.
//

#include "Laser.h"
#include "../../Engine/include/Game.h"
#include "../../Engine/include/CircleComponent.h"
#include "Asteroid.h"
#include "../../Engine/include/SpriteComponent.h"
#include "../../Engine/include/PhysicsMoveComponent.h"

Laser::Laser(Game* game, const Vector2 dir) : Actor(game)
{
    // create sprite comp
    auto* spriteComp = new SpriteComponent(this);
    spriteComp->SetTexture(game->GetTexture("Assets/Laser2.png"));

    // create move comp
    auto* moveComp = new PhysicsMoveComponent(this);
    moveComp->SetMass(0.1f);
    moveComp->AddForce(dir * 6000);

    mCircleComp = new CircleComponent(this);
    mCircleComp->SetRadius(11.0f);
}

void Laser::UpdateActor(const float deltaTime)
{
    mDeathTimer -= deltaTime;
    if (mDeathTimer <= 0.0f) SetState(EDead);
}