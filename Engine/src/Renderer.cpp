//
// Created by sloath on 11-Sep-26.
//

#include "include/Renderer.h"
#include "include/Engine.h"
#include "include/Constants.h"
#include "include/Shader.h"
#include "include/SpriteComponent.h"
#include "include/Texture.h"
#include "include/Mesh.h"
#include "include/VertexArray.h"
#include "include/MeshComponent.h"
#include <GL/glew.h>
#include <algorithm>

Renderer::Renderer(Engine* game) : mGame(game) {}

Renderer::~Renderer() = default;

bool Renderer::Initialize(const float screenWidth, const float screenHeight)
{
    bool success{ true };
    mScreenWidth = screenWidth;
    mScreenHeight = screenHeight;

    // set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    /*-----------------*/
    // request a color buffer with 8-bits per RGBA channel
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    mWindow = SDL_CreateWindow(
            windowTitle.c_str(),
            static_cast<int>(mScreenWidth), static_cast<int>(mScreenHeight),
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!mWindow)
    {
        SDL_Log("Unable to create Window and Renderer! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // create context
        mContext = SDL_GL_CreateContext(mWindow);
        if (!mContext)
        {
            SDL_Log("Unable to create OpenGL context! SDL Error: %s", SDL_GetError());
            success = false;
        }
        else
        {
            // init GLEW
            glewExperimental = GL_TRUE;
            if (glewInit() != GLEW_OK)
            {
                SDL_Log("Error initializing GLEW!");
                success = false;
            }
            else
            {
                if (!LoadShaders())
                {
                    SDL_Log("Failed to load shaders!");
                    success = false;
                }
                else
                {
                    // use vsync
                    if (!SDL_GL_SetSwapInterval(1))
                        SDL_Log("Warning: Unable to set VSync! SDL Error: %s", SDL_GetError());
                    CreateSpriteVerts();
                }
            }
        }
    }

    return success;
}

void Renderer::Shutdown()
{
    delete mSpriteVerts;
    mSpriteVerts = nullptr;

    mSpriteShader->Unload();
    delete mSpriteShader;
    mSpriteShader = nullptr;

    // mMeshShader->Unload();
    // delete mMeshShader;
    // mMeshShader = nullptr;

    SDL_GL_DestroyContext(mContext);
    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;
}

void Renderer::UnloadData()
{
    // destroy textures
    for (const auto& tex : mTextures)
        tex.second->Unload();
    mTextures.clear();

    // destroy meshes
    for (const auto& mesh : mMeshes)
        mesh.second->Unload();
    mMeshes.clear();
}

void Renderer::AddMeshComp(MeshComponent* meshComp)
{
    mMeshComps.emplace_back(meshComp);
}

void Renderer::RemoveMeshComp(const MeshComponent* meshComp)
{
    auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), meshComp);
    if (iter != mMeshComps.end())
    {
        std::iter_swap(mMeshComps.end() - 1, iter);
        mMeshComps.pop_back();
    }
}

void Renderer::Draw() const
{
    // set the clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // enable depth buffering / disable alpha blend
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    // set the basic mesh shader active
    mMeshShader->SetActive();
    // update view-prof matrix
    mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);
    for (const auto meshComp : mMeshComps)
        meshComp->Draw(mMeshShader);

    // disable depth test, enable alpha blend and sets func
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    // Set sprite shader and vertex array objs active
    mSpriteShader->SetActive();
    mSpriteVerts->SetActive();

    // draw all sprites
    for (const auto sprite : mSprites)
        sprite->Draw(mSpriteShader);

    //swap buffers,
    SDL_GL_SwapWindow(mWindow);
}

void Renderer::AddSprite(SpriteComponent* sprite)
{
    // find insertion point in sorted vector (first element with drawOrder higher)
    const int drawOrder = sprite->GetDrawOder();
    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); ++iter)
        if (drawOrder < (*iter)->GetDrawOder())
            break;
    mSprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(const SpriteComponent* sprite)
{
    if (const auto iter = std::find(mSprites.begin(), mSprites.end(), sprite); iter != mSprites.end())
        mSprites.erase(iter);
}

Texture* Renderer::GetTexture(const std::string& fileName)
{
    Texture* tex{ nullptr };

    // is texture already in map
    if (const auto iter = mTextures.find(fileName); iter != mTextures.end()) tex = iter->second;
    else
    {
        // const std::string filePath = "../../Game/" + fileName;
        tex = new Texture();
        // load from file
        if (tex->Load(fileName))
        {
            mTextures.emplace(fileName, tex);
        }
        else
        {
            delete tex;
            tex = nullptr;
        }
    }
    return tex;
}

Mesh* Renderer::GetMesh(const std::string& fileName)
{
    Mesh* mesh{nullptr};

    if (const auto iter = mMeshes.find(fileName); iter != mMeshes.end()) mesh = iter->second;
    else
    {
        mesh = new Mesh();
        if (mesh->Load(fileName, this))
            mMeshes.emplace(fileName, mesh);
        else
        {
            delete mesh;
            mesh =  nullptr;
        }
    }

    return mesh;
}

bool Renderer::LoadShaders()
{
    const std::string fullPath = "../../Game/";

    // create sprite shader
    mSpriteShader = new Shader();
    if (!mSpriteShader->Load(fullPath + "Shaders/Sprite.vert", fullPath + "Shaders/Sprite.frag"))
        return false;
    mSpriteShader->SetActive();
    const Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1920.0f, 1080.0f);
    mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

    // create basic mesh shader
    mMeshShader = new Shader();
    if (!mMeshShader->Load(fullPath + "Shaders/BasicMesh.vert", fullPath + "Shaders/BasicMesh.frag"))
        return false;
    mMeshShader->SetActive();
    mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
    mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f), mScreenWidth, mScreenHeight, 25.0f, 10000.0f);
    mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);

    return true;
}

void Renderer::CreateSpriteVerts()
{
    static float vertexBuffer[] = {
        -0.5f,  0.5f,   0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
        0.5f,   0.5f,   0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,
        0.5f,   -0.5f,  0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,
        -0.5f,  -0.5f,  0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f
    };

    static unsigned int indexBuffer[] = {
        0, 1, 2,
        2, 3, 0
    };

    mSpriteVerts = new VertexArray(vertexBuffer, 4, indexBuffer, 6);
}