//
// Created by sloath on 03-Sep-26.
//

#include "Game.h"
#include "FPSActor.h"
#include "PlaneActor.h"
#include "FollowActor.h"
#include <Engine/include/Engine.h>
#include <Engine/include/Renderer.h>
#include <Engine/include/Actor.h>
#include <Engine/include/InputSystem.h>
#include <Engine/include/MeshComponent.h>

Game::Game() = default;

Game::~Game() = default;

void Game::ProcessInput()
{
    Engine::ProcessInput();

    const InputState& state = mInputSystem->GetState();

    if (state.Keyboard.GetKeyState(SDL_SCANCODE_1) == EPressed) SwitchActor(FPSCam);
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_2) == EPressed) SwitchActor(FollowCam);
}

bool Game::ProcessGameEvent(SDL_Event* event)
{
    switch (event->type)
    {
    default:
        return false;
    }
}

void Game::LoadData()
{
    mInputSystem->SetRelativeMouseMode(true);

    mFPSActor = new FPSActor(this);
    mFollowActor = new FollowActor(this);

    mSphere = new Actor(this);
    mSphere->SetPosition(Vector3(200.0f, -75.0f, 0.0f));
    mSphere->SetScale(1.0f);
    auto* sphereMeshComp = new MeshComponent(mSphere);
    sphereMeshComp->SetMesh(mRenderer->GetMesh("Assets/Sphere.gpmesh"));

    mCube = new Actor(this);
    mCube->SetPosition(Vector3(200.0f, 75.0f, 0.0f));
    mCube->SetScale(100.0f);
    Quaternion q(Vector3::UnitY, -Math::PiOver2);
    q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
    mCube->SetRotation(q);
    auto* cubeMeshComp = new MeshComponent(mCube);
    cubeMeshComp->SetMesh(mRenderer->GetMesh("Assets/Cube.gpmesh"));

    // setup floor
    float start = -1250;
    float size = 250.0f;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            Actor* temp = new PlaneActor(this);
            temp->SetPosition(Vector3(start + i * size, start + j * size, -100.0f));
        }
    }

    // setup lights
    mRenderer->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
    DirectionalLight& dirLight = mRenderer->GetDirectionalLight();
    dirLight.mDirection = Vector3(0.0f, -0.7f, -0.7f);
    dirLight.mDiffuseColor = Vector3(0.78f, 0.88f, 1.f);
    dirLight.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);

    SwitchActor(static_cast<ActorName>(0));
}

void Game::UnloadData()
{
    // delete actors
    while (!mActors.empty())
        delete mActors.back();
}

void Game::SwitchActor(const ActorName actor) const
{
    // disable everything
    mFPSActor->SetState(Actor::EPaused);
    mFPSActor->SetVisible(false);

    mFollowActor->SetState(Actor::EPaused);
    mFollowActor->SetVisible(false);

    switch (actor)
    {
    case FPSCam:
        mFPSActor->SetState(Actor::EActive);
        mFPSActor->SetVisible(true);
        break;
    case FollowCam:
        mFollowActor->SetState(Actor::EActive);
        mFollowActor->SetVisible(true);
        break;
    default:
        break;
    }
}
