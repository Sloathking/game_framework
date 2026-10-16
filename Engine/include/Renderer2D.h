//
// Created by sloath on 10/15/26.
//

#ifndef RENDERER2D_H
#define RENDERER2D_H

#include "Renderer.h"
#include <SDL3/SDL.h>
#include <unordered_map>
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

    // load textures
    SDL_Texture* GetTexture(const std::string& fileName);

    void AddSprite(class SpriteComponent2D* sprite);
    void RemoveSprite(const SpriteComponent2D* sprite);

    // getters / setters
    [[nodiscard]] float GetScreenWidth() const { return mScreenWidth; }
    [[nodiscard]] float GetScreenHeight() const { return mScreenHeight; }

private:
    // renderer created by SDL
    SDL_Renderer* mRenderer{nullptr};

    // map of loaded Textures
    std::unordered_map<std::string, SDL_Texture*> mTextures{};

    // all sprites to draw
    std::vector<SpriteComponent2D*> mSprites{};

    float mScreenWidth{};
    float mScreenHeight{};
};


#endif //RENDERER2D_H
