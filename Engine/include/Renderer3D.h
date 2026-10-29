//
// Created by sloath on 11-Sep-26.
//

#ifndef RENDERER3D_H
#define RENDERER3D_H

#include "Renderer.h"
#include "Math.h"
#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

struct DirectionalLight
{
    Vector3 mDirection;
    Vector3 mDiffuseColor;
    Vector3 mSpecColor;
};

class Renderer3D : public Renderer
{
public:
    explicit Renderer3D(Engine* game);
    ~Renderer3D() override;

    // init / shutdown
    bool Initialize(float screenWidth, float screenHeight) override;
    void Shutdown() override;
    void UnloadData() override;

    void Draw() const override;

    bool SetVSync() override;

    // manage mesh components
    void AddMeshComp(class MeshComponent* meshComp);
    void RemoveMeshComp(const MeshComponent* meshComp);

    // load textures / meshes
    class Texture* GetTexture(const std::string& fileName);
    class Mesh* GetMesh(const std::string& fileName);

    void AddSprite(class SpriteComponent3D* sprite);
    void RemoveSprite(const SpriteComponent3D* sprite);

    void SetShaderName(const std::string& shaderName, MeshComponent* meshComp);

    // getters / setters
    [[nodiscard]] float GetScreenWidth() const { return mScreenWidth; }
    [[nodiscard]] float GetScreenHeight() const { return mScreenHeight; }

    void SetViewMatrix(const Matrix4& view) { mView = view; }

    void SetAmbientLight(const Vector3& ambient) { mAmbientLight = ambient; }

    DirectionalLight& GetDirectionalLight() { return mDirLight; }

private:
    bool LoadShaders();
    void CreateSpriteVerts();
    void SetLightUniforms(const class Shader* shader) const;

    // OpenGL context
    SDL_GLContext mContext{nullptr};

    // map of loaded Textures
    std::unordered_map<std::string, Texture*> mTextures{};

    // map of loaded Meshes
    std::unordered_map<std::string, Mesh*> mMeshes{};

    // vector of mesh comps
    std::vector<MeshComponent*> mMeshComps;
    std::unordered_map<std::string, Shader*> mShaderMap;
    std::unordered_map<std::string, std::vector<MeshComponent*>> mShaderMeshMap;

    // all sprites to draw
    std::vector<SpriteComponent3D*> mSprites{};

    Shader* mSpriteShader{};
    class VertexArray* mSpriteVerts{};

    Shader* mMeshShader{};
    Shader* mPhongShader{};

    // view / proj for 3D
    Matrix4 mView{};
    Matrix4 mProjection{};

    // lighting stuff
    Vector3 mAmbientLight{};
    DirectionalLight mDirLight{};

    float mScreenWidth{};
    float mScreenHeight{};
};

#endif //RENDERER3D_H
