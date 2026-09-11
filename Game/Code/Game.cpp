//
// Created by sloath on 03-Sep-26.
//

#include "Game.h"
#include <Engine/include/Actor3D.h>
#include <Engine/include/InputSystem.h>
#include <Engine/include/MeshComponent.h>
#include <Engine/include/Mesh.h>

#include "Engine/include/Renderer.h"

Game::Game() = default;

Game::~Game() = default;

void Game::ProcessInput()
{
    Engine::ProcessInput();
}

void Game::LoadData()
{
    mCamActor = new Actor3D(this);
    mCamActor->SetPosition(Vector3(0,0,0));

    mSphere = new Actor3D(this);
    mSphere->SetPosition(Vector3(200.0f, -75.0f, 0.0f));
    mSphere->SetScale(8.0f);
    auto* sphereMeshComp = new MeshComponent(mSphere);
    sphereMeshComp->SetMesh(mRenderer->GetMesh("Assets/Sphere.gpmesh"));

    mCube = new Actor3D(this);
    mCube->SetPosition(Vector3(200.0f, 75.0f, 0.0f));
    mCube->SetScale(100.0f);
    Quaternion q(Vector3::UnitY, -Math::PiOver2);
    q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
    mCube->SetRotation(q);
    auto* cubeMeshComp = new MeshComponent(mCube);
    cubeMeshComp->SetMesh(mRenderer->GetMesh("Assets/Cube.gpmesh"));

    // loc of camera
    const Vector3 eye = mCamActor->GetPosition();

    // point 10 units in front of camera
    const Vector3 target = mCamActor->GetPosition() + mCamActor->GetForward() * 10.0f;

    Matrix4 view = Matrix4::CreateLookAt(eye, target, Vector3::UnitZ);
}

void Game::UnloadData()
{
    // delete actors
    while (!mActors.empty())
        delete mActors.back();
}
