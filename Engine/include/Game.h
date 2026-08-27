//
// Created by sloath on 06-Aug-26.
//

#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

class Game
{
public:
    Game();

    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(const Actor* actor);

    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(const SpriteComponent* sprite);

    SDL_Texture* GetTexture(const std::string& fileName);

    // This is used for Input System to have a ref to the window for RELATIVE mode
    SDL_Window* GetWindow () const { return mWindow; }

    // game functions

private:
    // helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput() const;
    void LoadData();
    void UnloadData();

    // window created by SDL
    SDL_Window* mWindow{nullptr};

    // renderer created by SDL
    SDL_Renderer* mRenderer{nullptr};

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

    // map of loaded textures
    std::unordered_map<std::string, SDL_Texture*> mTextures;

    // all the drawn sprite components
    std::vector<SpriteComponent*> mSprites;

    // camera stuff
    class CameraComponent* mCurrCamera;
    // game-specific stuff
    class Dot* mDot;

};

#endif //GAME_H