//
// Created by sloath on 06-Aug-26.
//

#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

#include "Actor.h"

class Game
{
public:
    Game();

    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);

    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);

    SDL_Texture* GetTexture(const std::string& fileName);

    SDL_Renderer* GetRenderer() const { return mRenderer; }

    // game functions


private:
    // helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput() const;
    void LoadData();
    void UnloadData() const;

    // window created by SDL
    SDL_Window* mWindow;

    // renderer created by SDL
    SDL_Renderer* mRenderer;

    // game should continue to run
    bool mIsRunning;

    // previous tick count
    Uint64 mTicksCount;

    // vectors to hold active Actors and pending Actors
    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;
    bool mUpdatingActors;

    // map of loaded textures
    std::unordered_map<std::string, SDL_Texture*> mTextures;

    // all the drawn sprite components
    std::vector<SpriteComponent*> mSprites;

};

#endif //GAME_H
