//
// Created by sloath on 18-Aug-26.
//

#include "Laser.h"
#include "../Engine/include/Game.h"
#include "../Engine/include/CircleComponent.h"
#include "Asteroid.h"
#include "../Engine/include/SpriteComponent.h"
#include "../Engine/include/MoveComponent.h"

Laser::Laser(Game* game) : Actor(game)
{
    // create sprite comp
    auto* spriteComp = new SpriteComponent(this);
    spriteComp->SetTexture(game->GetTexture("Assets/Laser2.png"));

    // create move comp
    auto* moveComp = new MoveComponent(this);
    moveComp->SetForwardSpeed(800.0f);

    mCircleComp = new CircleComponent(this);
    mCircleComp->SetRadius(11.0f);
}

void Laser::UpdateActor(const float deltaTime)
{
    mDeathTimer -= deltaTime;
    if (mDeathTimer <= 0.0f) SetState(EDead);

    // does Laser intersect with an Asteroid
    for (const auto asteroid : GetGame()->GetAsteroids())
    {
        if (Intersect(*mCircleComp, *asteroid->GetCircle()))
        {
            // if this laser intersects with an asteroid, set ourselves and the asteroid to dead
            SetState(EDead);
            asteroid->SetState(EDead);
            break;
        }
    }
}