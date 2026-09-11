//
// Created by sloath on 11-Sep-26.
//

#ifndef RENDERER_H
#define RENDERER_H

#include "Math.h"
#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

class Renderer
{
public:
    explicit Renderer(class Engine* game);
    ~Renderer();

    // init / shutdown
    bool Initialize(float screenWidth, float screenHeight);
    void Shutdown();
    void UnloadData();

    // manage mesh components
    void AddMeshComp(class MeshComponent* meshComp);
    void RemoveMeshComp(const MeshComponent* meshComp);

    // load textures / meshes
    void Draw() const;

    class Texture* GetTexture(const std::string& fileName);
    class Mesh* GetMesh(const std::string& fileName);

    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(const SpriteComponent* sprite);


    SDL_Window* GetWindow() const { return mWindow; }

private:
    bool LoadShaders();
    void CreateSpriteVerts();

    Engine* mGame;

    // window created by SDL
    SDL_Window* mWindow{nullptr};

    // OpenGL context
    SDL_GLContext mContext{nullptr};

    // map of loaded Textures
    std::unordered_map<std::string, Texture*> mTextures{};

    // map of loaded Meshes
    std::unordered_map<std::string, Mesh*> mMeshes{};

    // vector of mesh comps
    std::vector<MeshComponent*> mMeshComps;

    // all sprites to draw
    std::vector<SpriteComponent*> mSprites{};

    class Shader* mSpriteShader{};
    class VertexArray* mSpriteVerts{};

    Shader* mMeshShader{};

    // view / proj for 3D
    Matrix4 mView{};
    Matrix4 mProjection{};

    float mScreenWidth{};
    float mScreenHeight{};
};

#endif //RENDERER_H
