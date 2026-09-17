//
// Created by sloath on 03-Sep-26.
//

#include "Game.h"
#include "FPSActor.h"
#include "PlaneActor.h"
#include <Engine/include/Engine.h>
#include <Engine/include/Renderer.h>
#include <Engine/include/Actor.h>
#include <Engine/include/InputSystem.h>
#include <Engine/include/MeshComponent.h>


Game::Game()
{

}

Game::~Game() = default;

void Game::ProcessInput()
{
    Engine::ProcessInput();
}

void Game::LoadData()
{
    mInputSystem->SetRelativeMouseMode(true);

    mFPSActor = new FPSActor(this);
    mFPSActor->SetPosition(Vector3(0,0,0));

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

}

void Game::UnloadData()
{
    // delete actors
    while (!mActors.empty())
        delete mActors.back();
}
