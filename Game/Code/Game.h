//
// Created by sloath on 03-Sep-26.
//

#ifndef GAME_H
#define GAME_H

#include <Engine/include/Engine.h>
#include <Engine/include/Math.h>

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

    class CameraActor* mCamActor{};

    Actor* mSphere{};
    Actor* mCube{};
};

#endif //GAME_H
