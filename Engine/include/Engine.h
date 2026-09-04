//
// Created by sloath on 06-Aug-26.
//

#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

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

    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(const SpriteComponent* sprite);

    SDL_GPUShader* GetShader(const std::string& shaderFileName,
        Uint32 samplerCount, Uint32 storageTextureCount, Uint32 storageBufferCount, Uint32 uniformBufferCount);


    SDL_Texture* GetTexture(const std::string& fileName);

    // This is used for Input System to have a ref to the window for RELATIVE mode
    [[nodiscard]] SDL_Window* GetWindow () const { return mWindow; }

    // camera stuff
    //void SetMainCamera(class CameraComponent* camera) { mCamera = camera; }

protected:
    virtual void LoadData() = 0;
    virtual void UnloadData() = 0;

    // window created by SDL
    SDL_Window* mWindow{nullptr};

    // sdl gpu device
    SDL_GPUDevice* mDevice{nullptr};
    SDL_GPUGraphicsPipeline* mPipeline{nullptr};

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

    // shaders
    SDL_GPUShader* vertShader{};
    SDL_GPUShader* fragShader{};

    // map of loaded shaders
    std::unordered_map<std::string, SDL_GPUShader*> mShaders;

    // map of loaded textures
    std::unordered_map<std::string, SDL_Texture*> mTextures;

    // all the drawn sprite components
    std::vector<SpriteComponent*> mSprites;

    // camera stuff
    // Actor* mCamActor{};
    // CameraComponent* mCamera;

private:
    // helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

};

#endif //ENGINE_H