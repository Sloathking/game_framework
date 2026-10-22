//
// Created by sloath on 10/15/26.
//

#include "include/Renderer2D.h"
#include "include/Engine.h"
#include "include/Constants.h"
#include "include/Camera2D.h"
#include "include/Actor2D.h"
#include "include/SpriteComponent2D.h"
#include <SDL3/SDL_log.h>
#include <algorithm>

Renderer2D::Renderer2D(Engine* game) : Renderer(game) {}

Renderer2D::~Renderer2D() = default;

bool Renderer2D::Initialize(const float screenWidth, const float screenHeight)
{
    bool success{ true };
    mScreenWidth = screenWidth;
    mScreenHeight = screenHeight;

    if (SDL_CreateWindowAndRenderer(windowTitle.c_str(),
        static_cast<int>(mScreenWidth), static_cast<int>(mScreenHeight),
        SDL_WINDOW_RESIZABLE,
        &mWindow, &mRenderer) == false)
    {
        SDL_Log("Unable to create Window and Renderer! SDL Error: %s", SDL_GetError());
        success = false;
    }
    else
    {
        success = SetVSync();
    }

    SDL_SetRenderLogicalPresentation(mRenderer,mScreenWidth,mScreenHeight,SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);

    return success;
}

void Renderer2D::Shutdown()
{
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
        mScreenWidth = x;
        mScreenHeight = y;
        mCamera->SetWindowSize(mScreenWidth, mScreenHeight);
        SDL_SetRenderLogicalPresentation(mRenderer, mScreenWidth, mScreenHeight, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
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

bool Renderer2D::IsInCamera(const Vector2& spritePos, const Vector2& camPos) const
{
    if (spritePos.x >= camPos.x and spritePos.x <= camPos.x + mScreenWidth * mRenderScale
        and spritePos.y >= camPos.y and spritePos.y <= camPos.y + mScreenHeight * mRenderScale)
        return true;
    return false;
}

void Renderer2D::Draw() const
{
    SDL_SetRenderDrawColor(mRenderer, 25, 25, 25, 255);
    SDL_RenderClear(mRenderer);

    // Vector2 camPos = mCamera->GetPosition();
    // camPos.x = -camPos.x;
    // camPos.y = -camPos.y;

    const Vector2 offset = mCamera->GetPosition();
    for (const auto sprite : mSprites)
    {
        // SDL_Log("Offset - X: %F | Y: %f", offset.x, offset.y);
        const auto ownerPos = dynamic_cast<Actor2D*>(sprite->GetOwner())->GetPosition();
        const auto ownerOffset = ownerPos - offset;
        if (IsInCamera(ownerPos, offset))
            sprite->Draw(mRenderer, offset);
        //sprite->Draw(mRenderer, offset);

        SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
        SDL_FRect rect{ .x = ownerOffset.x - 1, .y = ownerOffset.y - 1, .w = 2, .h = 2 };
        SDL_RenderFillRect(mRenderer, &rect);
    }

    // SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    // const SDL_FRect dotRect{.x = mDot->GetPosition().x + camPos.x - 5, .y = mDot->GetPosition().y + camPos.y - 5, .w = 10, .h = 10};
    // SDL_RenderFillRect(mRenderer, &dotRect);

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
            tex = SDL_CreateTextureFromSurface(mRenderer, surf);
            if (tex = SDL_CreateTextureFromSurface(mRenderer, surf), !tex)
                SDL_Log("Unable to create texture! SDL Error: %s", SDL_GetError());
            else
            {
                SDL_DestroySurface(surf);
                mTextures.emplace(fileName, tex);
            }
        }
    }
    return tex;
}

void Renderer2D::AddSprite(SpriteComponent2D* sprite)
{
    // find insertion point in sorted vector (first element with drawOrder higher)
    const int drawOrder = sprite->GetDrawOder();
    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); ++iter)
        if (drawOrder < (*iter)->GetDrawOder())
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
    mRenderScale = scale;
    SDL_SetRenderLogicalPresentation(mRenderer, mScreenWidth, mScreenHeight, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
}