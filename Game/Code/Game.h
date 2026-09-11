//
// Created by sloath on 03-Sep-26.
//

#ifndef GAME_H
#define GAME_H

#include <Engine/include/Engine.h>
#include <Engine/include/Math.h>
#include <Engine/include/Constants.h>

typedef struct PositionTextureVertex
{
    float x, y, z;
    float u, v;
} PositionTextureVertex;

class Game : public Engine
{
public:
    Game();
    ~Game() override;


protected:
    void ProcessInput() override;

    void LoadData() override;
    void UnloadData() override;

private:
    std::vector<Actor*> mSpriteActors;

    //TODO: Update sizes for moving Camera
    Vector2 mWorldSize{1920, 1080};

    class Mesh* mMesh{};
    class Actor3D* mCamActor;

    Actor3D* mSphere;
    Actor3D* mCube;
};

#endif //GAME_H
