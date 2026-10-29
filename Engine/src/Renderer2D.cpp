//
// Created by sloath on 10/15/26.
//

#include "include/Renderer2D.h"
#include "include/Engine.h"
#include "include/Constants.h"
#include "include/UIScreen.h"
#include "include/Camera2D.h"
#include "include/Actor2D.h"
#include "include/SpriteComponent2D.h"
#include <SDL3/SDL_log.h>
#include <SDL3_image/SDL_image.h>
#include <algorithm>

Renderer2D::Renderer2D(Engine* game) : Renderer(game) {}

Renderer2D::~Renderer2D() = default;

bool Renderer2D::Initialize(const float windowWidth, const float windowHeight)
{
    bool success{ true };
    mWindowWidth = windowWidth;
    mWindowHeight = windowHeight;

    if (SDL_CreateWindowAndRenderer(windowTitle.c_str(),
        static_cast<int>(mWindowWidth), static_cast<int>(mWindowHeight),
        SDL_WINDOW_RESIZABLE,
        &mWindow, &mRenderer) == false)
    {
        SDL_Log("Unable to create Window and Renderer! SDL Error: %s", SDL_GetError());
        success = false;
    }
    else
    {
        success = SetVSync();
        if (!SDL_SetRenderScale(mRenderer, mRenderScale, mRenderScale))
        {
            SDL_Log("Unable to set Render Scale! SDL Error: %s", SDL_GetError());
            success = false;
        }
    }
    return success;
}

void Renderer2D::Shutdown()
{
    SDL_DestroyRenderer(mRenderer);
    mRenderer = nullptr;

    SDL_DestroyWindow(mWindow);
    mWindow = nullptr;
}

void Renderer2D::ProcessEvent(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_EVENT_WINDOW_RESIZED:
    {
        int x, y;
        if (!SDL_GetWindowSize(mWindow, &x, &y))
        {
            SDL_Log("SDL_EVENT_WINDOW_RESIZED - Error: %s", SDL_GetError());
            //mIsRunning = false;
            break;
        }
        mWindowWidth = x;
        mWindowHeight = y;
        mCamera->SetWindowSize(mWindowWidth, mWindowHeight);
        if (!SDL_SetRenderScale(mRenderer, mRenderScale, mRenderScale))
            SDL_Log("Unable to set Render Scale! SDL Error: %s", SDL_GetError());
        break;
    }
    default:
        break;
    }
}

void Renderer2D::UnloadData()
{
    // destroy textures
    for (const auto& tex : mTextures)
        SDL_DestroyTexture(tex.second);
    mTextures.clear();
}

bool Renderer2D::IsInCamera(const Vector2& spritePos, const int texWidth) const
{
    if (spritePos.x >= 0 - texWidth and spritePos.x <= mWindowWidth + texWidth
        and spritePos.y >= 0 - texWidth and spritePos.y <= mWindowHeight + texWidth)
        return true;
    return false;
}

void Renderer2D::Draw() const
{
    SDL_SetRenderDrawColor(mRenderer, 25, 25, 25, 255);
    SDL_RenderClear(mRenderer);

    SDL_SetRenderScale(mRenderer, mRenderScale, mRenderScale);

    if (mCamera)
    {
        const Vector2 camOffset = mCamera->GetCameraOffset(mRenderScale);
        for (const auto sprite : mSprites)
        {
            const auto actorPos = sprite->GetOwner()->GetPosition();
            if (const auto actorOffset = actorPos - camOffset; IsInCamera(actorOffset * mRenderScale, sprite->GetTexWidth()))
            {
                sprite->Draw(mRenderer, camOffset, 1.0f);

                SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
                SDL_FRect rect{ .x = actorOffset.x - 1, .y = actorOffset.y - 1, .w = 2, .h = 2 };
                SDL_RenderFillRect(mRenderer, &rect);
            }
        }
    }

    // collection of UI elements
    // iterate through them calling Draw() function
    // draw gets called in an order that gives it correct layers
    SDL_SetRenderScale(mRenderer, mUIScale, mUIScale);
    for (const auto ui : mGame->GetUIStack())
        ui->Draw(mRenderer, mUIScale);

    SDL_RenderPresent(mRenderer);
}

bool Renderer2D::SetVSync()
{
    bool success{true};
    if (SDL_SetRenderVSync(mRenderer, vSyncEnabled ? 1 : SDL_RENDERER_VSYNC_DISABLED) == false)
    {
        SDL_Log("Could not enable VSync! SDL Error: %s", SDL_GetError());
        success = false;
    }
    return success;
}

SDL_Texture* Renderer2D::GetTexture(const std::string& fileName)
{
    SDL_Texture* tex{ nullptr };

    // is texture already in map
    if (const auto iter = mTextures.find(fileName); iter != mTextures.end()) tex = iter->second;
    else
    {
        if (SDL_Surface* surf = IMG_Load(fileName.c_str()); !surf)
        {
            SDL_Log("Failed to load texture file: %s", fileName.c_str());
        }
        else
        {
            if (tex = SDL_CreateTextureFromSurface(mRenderer, surf), !tex)
                SDL_Log("Unable to create texture! SDL Error: %s", SDL_GetError());
            else
                mTextures.emplace(fileName, tex);
            SDL_DestroySurface(surf);
        }
    }
    return tex;
}

void Renderer2D::AddSprite(SpriteComponent2D* sprite)
{
    // find insertion point in sorted vector (first element with drawOrder higher)
    const int drawOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); ++iter)
        if (drawOrder < (*iter)->GetDrawOrder())
            break;
    mSprites.insert(iter, sprite);
}

void Renderer2D::RemoveSprite(const SpriteComponent2D* sprite)
{
    if (const auto iter = std::find(mSprites.begin(), mSprites.end(), sprite); iter != mSprites.end())
        mSprites.erase(iter);
}

void Renderer2D::SetRenderScale(const float scale)
{
    mRenderScale = Math::Clamp(scale, mMinRenderScale, mMaxRenderScale);
    if (!SDL_SetRenderScale(mRenderer, mRenderScale, mRenderScale))
        SDL_Log("Unable to set Render Scale! SDL Error: %s", SDL_GetError());
}