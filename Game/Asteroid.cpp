//
// Created by sloath on 17-Aug-26.
//

#include "Asteroid.h"

#include "../Engine/include/Constants.h"
#include "../Engine/include/Game.h"
#include "../Engine/include/Random.h"
#include "../Engine/include/SpriteComponent.h"
#include "../Engine/include/MoveComponent.h"

Asteroid::Asteroid(Game* game) : Actor(game)
{
    // init to random position and rotation
    const Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(windowWidth, windowHeight));
    SetPosition(randPos);
    SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

    // create sprit comp and set texture
    auto* spriteComp = new SpriteComponent(this);
    spriteComp->SetTexture(game->GetTexture(("Assets/Asteroid.png")));

    // create move comp and set forward speed
    auto* moveComp = new MoveComponent(this);
    moveComp->SetForwardSpeed(150.0f);

    game->AddAsteroid(this);
}