//
// Created by sloath on 10/15/26.
//

#ifndef RENDERER2D_H
#define RENDERER2D_H

#include "Renderer.h"
#include <SDL3/SDL.h>
#include <unordered_map>
#include "Math.h"
#include <vector>
#include <string>

class Renderer2D : public Renderer
{
public:
    explicit Renderer2D(Engine* game);
    ~Renderer2D() override;

    // init / shutdown
    bool Initialize(float screenWidth, float screenHeight) override;
    void Shutdown() override;
    void UnloadData();

    void Draw() const override;

    bool SetVSync() override;

    void ProcessEvent(const SDL_Event& event) override;

    // load textures
    SDL_Texture* GetTexture(const std::string& fileName);

    void AddSprite(class SpriteComponent2D* sprite);
    void RemoveSprite(const SpriteComponent2D* sprite);

    // getters / setters
    [[nodiscard]] int GetScreenWidth() const { return mScreenWidth; }
    [[nodiscard]] int GetScreenHeight() const { return mScreenHeight; }

    float GetRenderScale() const { return mRenderScale; }
    void SetRenderScale(float scale);

    void SetCamera(class Camera2D* cam) { mCamera = cam; }

private:
    bool IsInCamera(const class Vector2& spritePos, const Vector2& camPos) const;

    // renderer created by SDL
    SDL_Renderer* mRenderer{nullptr};

    // render scaling
    float mRenderScale{1.0f};

    // map of loaded Textures
    std::unordered_map<std::string, SDL_Texture*> mTextures{};

    // all sprites to draw
    std::vector<SpriteComponent2D*> mSprites{};

    int mScreenWidth{};
    int mScreenHeight{};

    Camera2D* mCamera;
};


#endif //RENDERER2D_H
