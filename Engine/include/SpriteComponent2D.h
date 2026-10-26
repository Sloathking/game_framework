//
// Created by sloath on 10/15/26.
//

#ifndef SPRITECOMPONENT2D_H
#define SPRITECOMPONENT2D_H

#include "Component2D.h"
#include "Math.h"
#include <SDL3/SDL.h>

class SpriteComponent2D : public Component2D
{
public:
    explicit SpriteComponent2D(Actor2D * owner, int drawOrder = 100);
    ~SpriteComponent2D() override;

    virtual void Draw(SDL_Renderer * renderer, Vector2 offset, float scaleFactor);

    virtual void SetTexture(SDL_Texture * texture);

    [[nodiscard]] bool GetVisibility() const { return mIsVisible; }
    void SetVisibility(const bool visible) { mIsVisible = visible; }

    [[nodiscard]] int GetDrawOrder() const { return mDrawOrder; }

    [[nodiscard]] int GetTexWidth() const { return mTexWidth; }

    [[nodiscard]] int GetTexHeight() const { return mTexHeight; }

     [[nodiscard]] Vector2 GetOffset() const { return mOffset;}
    void SetOffset(const Vector2 vec) { mOffset = vec; }

    void SetClip(const SDL_FRect rect) { mClip = rect; }

    [[nodiscard]] SDL_FlipMode GetFlipMode() const { return mSpriteFlipMode; }
    void SetFlipMode(const SDL_FlipMode flip) { mSpriteFlipMode = flip; }

protected:
    bool mIsVisible{true};

    SDL_Texture* mTexture{ nullptr };
    int mDrawOrder;
    int mTexWidth{0};
    int mTexHeight{0};

    Vector2 mOffset{Vector2::Zero};

    SDL_FRect mClip{};

    SDL_FlipMode mSpriteFlipMode{SDL_FLIP_NONE};

};

#endif //SPRITECOMPONENT2D_H
