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

    class Texture* GetTexture(const std::string& fileName);

    class Mesh* GetMesh(const std::string& fileName);

    static SDL_Surface* LoadImage(const std::string& fileName, int numChannels);

    bool LoadShaders(const std::string& vertName, const std::string& fragName);

    // This is used for Input System to have a ref to the window for RELATIVE mode
    [[nodiscard]] SDL_Window* GetWindow () const { return mWindow; }

protected:
    virtual void ProcessInput();

    virtual void LoadData() = 0;
    virtual void UnloadData() = 0;
    void CreateSpriteVerts();

    // window created by SDL
    SDL_Window* mWindow{nullptr};

    // OpenGL context
    SDL_GLContext mContext{nullptr};

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

    // map of loaded meshes
    std::unordered_map<std::string, Mesh*> mMeshes;

    // map of loaded textures
    std::unordered_map<std::string, Texture*> mTextures;

    // all the drawn sprite components
    std::vector<SpriteComponent*> mSprites;
    class VertexArray* mSpriteVerts{};


private:
    // helper functions for the game loop
    void UpdateGame();
    void GenerateOutput();

    class Shader* mSpriteShader;

};

#endif //ENGINE_H