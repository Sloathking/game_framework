//
// Created by sloath on 17-Aug-26.
//

#include "Asteroid.h"
#include <Engine/include/Engine.h>
#include <Engine/include/Renderer2D.h>
#include <Engine/include/Random.h>
#include <Engine/include/SpriteComponent2D.h>
#include <Engine/include/CircleComponent.h>

Asteroid::Asteroid(Engine* game) : Actor(game)
{
    auto* renderer = dynamic_cast<Renderer2D*>(game->GetRenderer());

    // init to random position and rotation
    const Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(5120, 5120));
    Vector3 newPos = GetPosition();
    newPos += Vector3(randPos.x, randPos.y, newPos.z);
    SetPosition(newPos);

    // create sprit comp and set texture
    auto* spriteComp = new SpriteComponent2D(this);
    spriteComp->SetTexture(renderer->GetTexture(("Assets/Asteroid.png")));
    spriteComp->SetAnchor(SpriteComponent2D::AnchorPoint::CenterCenter);
    spriteComp->SetCenter(SpriteComponent2D::AnchorPoint::CenterCenter);

    // create move comp and set forward speed
    // mMoveComp = new PhysicsMoveComponent(this);
    // mMoveComp->SetMass(1.0f);
    // mMoveComp->AddForce(GetForward() * 1000);

    mCircleComp = new CircleComponent(this);
    mCircleComp->SetRadius(40.0f);
}

Asteroid::~Asteroid() = default;

void Asteroid::UpdateActor(float deltaTime)
{

}