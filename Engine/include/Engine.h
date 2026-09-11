//
// Created by sloath on 06-Aug-26.
//

#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>
#include <vector>

class Engine
{
public:
    Engine();
    virtual ~Engine();

    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(const Actor* actor);

    [[nodiscard]] class Renderer* GetRenderer() const { return mRenderer; }

protected:
    virtual void ProcessInput();

    virtual void LoadData() = 0;
    virtual void UnloadData() = 0;

    // renderer
    Renderer* mRenderer{nullptr};

    // game should continue to run
    bool mIsRunning{true};

    // previous tick count
    Uint64 mTicksCount{0};

    // input system for stuff **UPDATE LATER**
    class InputSystem* mInputSystem{};

    // vectors to hold active Actors and pending Actors
    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;
    bool mUpdatingActors{false};

private:
    // helper functions for the game loop
    void UpdateGame();
    void GenerateOutput();

};

#endif //ENGINE_H