//
// Created by sloath on 03-Sep-26.
//

#ifndef GAME_H
#define GAME_H

#include <Engine/include/Engine.h>

enum ActorName
{
    FPSCam = 0,
    FollowCam = 1,
    OrbitCam = 2,
    TopDownCam = 3,
};

class Game : public Engine
{
public:
    Game();
    ~Game() override;

protected:
    void ProcessInput() override;
    bool ProcessGameEvent(SDL_Event* event) override;

    void LoadData() override;
    void UnloadData() override;

private:
    void SwitchActor(ActorName) const;

    std::vector<Actor*> mSpriteActors;

    class FPSActor* mFPSActor{};
    class FollowActor* mFollowActor{};
    class OrbitActor* mOrbitActor{};
    class TopDownActor* mTopDownActor{};

    Actor* mSphere{};
    Actor* mCube{};
};

#endif //GAME_H
