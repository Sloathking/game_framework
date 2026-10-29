//
// Created by sloath on 06-Aug-26.
//

#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

enum RendererType{ TwoD, ThreeD };

class Engine
{
public:
    enum GameState { EGameplay, EPaused, EQuit };

    Engine();
    virtual ~Engine();

    bool Initialize(RendererType);
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(const Actor* actor);

    [[nodiscard]] GameState GetState() const { return mGameState; }
    void SetState(const GameState state) { mGameState = state; }

    [[nodiscard]] class Renderer* GetRenderer() const { return mRenderer; }

    [[nodiscard]] class Font* GetFont(const std::string& fileName);

    [[nodiscard]] std::vector<class UIScreen*>& GetUIStack() { return mUIStack;}
    void PushUI(UIScreen* screen) { mUIStack.emplace_back(screen); }

    void SetRelativeMouseMode(bool value) const;

protected:
    // current engine/game state
    GameState mGameState{ EGameplay };

    virtual void ProcessInput();
    virtual bool ProcessGameEvent(SDL_Event* event) = 0;

    virtual void LoadData() = 0;
    virtual void UnloadData();

    // renderer
    Renderer* mRenderer{nullptr};

    // previous tick count
    Uint64 mTicksCount{0};

    // input system for stuff **UPDATE LATER**
    class InputSystem* mInputSystem{};

    // vectors to hold active Actors and pending Actors
    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;
    bool mUpdatingActors{false};

    // fonts
    std::unordered_map<std::string, Font*> mFonts;

    // UI stuff
    std::vector<UIScreen*> mUIStack;

private:
    // helper functions for the game loop
    void UpdateGame();
    void GenerateOutput() const;

};

#endif //ENGINE_H