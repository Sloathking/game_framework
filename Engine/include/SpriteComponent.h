//
// Created by sloath on 06-Aug-26.
//
// figure out anchor point stuff
#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Component.h"
#include <SDL3_image/SDL_image.h>
#include <unordered_map>
#include "../../Engine/include/Math.h"

class SpriteComponent : public Component
{
public:
    enum AnchorPoint { TopLeft = 0, TopCenter = 1, TopRight = 2, CenterLeft = 3, CenterCenter = 4, CenterRight = 5, BottomLeft = 6, BottomCenter = 7, BottomRight = 8 };

    // symbolic constant
    static constexpr float kOriginalSize = -1.0f;

    explicit SpriteComponent(Actor* owner, int drawOrder = 100);
    ~SpriteComponent() override;

    virtual void Draw(SDL_Renderer* renderer, Vector2 offset, const SDL_FRect* clip, float width, float height);

    virtual void SetTexture(SDL_Texture* texture);

    [[nodiscard]] bool GetVisibility() const { return mIsVisible; }
    void SetVisibility(const bool visible) { mIsVisible = visible; }

    [[nodiscard]] int GetDrawOder() const { return mDrawOrder; }

    [[nodiscard]] int GetTexWidth() const { return mTexWidth; }

    [[nodiscard]] int GetTextHeight() const { return mTexHeight; }

     [[nodiscard]] Vector2 GetOffset() const { return mOffset;}
    void SetOffset(const Vector2 vec) { mOffset = vec; }

    double GetRotation() const { return mRotation; }
    void SetRotation(const float rotation) { mRotation = rotation; }

    [[nodiscard]] SDL_FlipMode GetFlipMode() const { return spriteFlipMode; }
    void SetFlipMode(const SDL_FlipMode flip) { spriteFlipMode = flip; }

    [[nodiscard]] AnchorPoint GetAnchor() const { return mAnchor; }
    void SetAnchor(const AnchorPoint anchor) { mAnchor = anchor; }

    [[nodiscard]] AnchorPoint GetCenter() const { return mRotPoint; }
    void SetCenter(const AnchorPoint rotPoint) { mRotPoint = rotPoint; }

protected:
    SDL_FPoint* GetCenter(const SDL_FRect& dstRect);

    bool mIsVisible{true};

    std::unordered_map<AnchorPoint, Vector2> anchorOffsets{};
    std::unordered_map<AnchorPoint, Vector2> rotOffsets{};

    SDL_Texture* mTexture{ nullptr };
    int mDrawOrder;
    int mTexWidth{ 0 };
    int mTexHeight{ 0 };

    Vector2 mOffset{Vector2::Zero};

    float mRotation{ 0.0 };

    SDL_FlipMode spriteFlipMode{SDL_FLIP_NONE};

    SDL_FPoint mCenter{.x = 0.0f,.y = 0.0f};

    AnchorPoint mAnchor{ TopLeft };
    AnchorPoint mRotPoint{ TopLeft };

};

#endif //SPRITECOMPONENT_H
