//
// Created by sloath on 10/15/26.
//

#ifndef RENDERER2D_H
#define RENDERER2D_H

#include "Renderer.h"
#include "Math.h"
#include "Camera2D.h"
#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

class Renderer2D : public Renderer
{
public:
    explicit Renderer2D(Engine* game);
    ~Renderer2D() override;

    // init / shutdown
    bool Initialize(float windowWidth, float windowHeight) override;
    void Shutdown() override;
    void UnloadData() override;

    void Draw() const override;

    bool SetVSync() override;

    void ProcessEvent(const SDL_Event& event) override;

    // load textures
    SDL_Texture* GetTexture(const std::string& fileName);

    void AddSprite(class SpriteComponent2D* sprite);
    void RemoveSprite(const SpriteComponent2D* sprite);

    // getters / setters
    [[nodiscard]] SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
    [[nodiscard]] Vector2 GetWindowSize() const { return Vector2(mWindowWidth, mWindowHeight); }

    float GetRenderScale() const { return mRenderScale; }
    void SetRenderScale(float scale);

    void SetCamera(Camera2D* cam) { mCamera = cam; mCamera->SetWindowSize(mWindowWidth, mWindowHeight); }

private:
    bool IsInCamera(const Vector2& spritePos, int texWidth) const;

    // renderer created by SDL
    SDL_Renderer* mRenderer{nullptr};

    // render scaling
    float mRenderScale{1.0f};
    float mMaxRenderScale{2.0f};
    float mMinRenderScale{0.1f};

    // UI scale
    float mUIScale{1.0f};
    float mMaxUIScale{2.0f};
    float mMinUIScale{0.1f};

    // map of loaded Textures
    std::unordered_map<std::string, SDL_Texture*> mTextures{};

    // all sprites to draw
    std::vector<SpriteComponent2D*> mSprites{};

    float mWindowWidth{};
    float mWindowHeight{};

    Camera2D* mCamera{};

};


#endif //RENDERER2D_H
