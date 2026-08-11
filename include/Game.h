//
// Created by sloath on 06-Aug-26.
//

#ifndef CLION_GAME_PROGRAMMING_GAME_H
#define CLION_GAME_PROGRAMMING_GAME_H

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
    void RemoveActor(class Actor* actor);

    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);

    SDL_Renderer* GetRenderer() const { return mRenderer; }
    SDL_Texture* GetTexture(const std::string& fileName);

private:
    // helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();

    // window created by SDL
    SDL_Window* mWindow;

    // renderer created by SDL
    SDL_Renderer* mRenderer;

    // game should continue to run
    bool mIsRunning;

    // previous tick count
    Uint64 mTicksCount;

    // vectors to hold active Actors and pending Actors
    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;
    bool mUpdatingActors;

    // map of loaded textures
    std::unordered_map<std::string, SDL_Texture*> mTextures;

    // all the drawn sprite components
    std::vector<class SpriteComponent*> mSprites;
};

#endif //CLION_GAME_PROGRAMMING_GAME_H
