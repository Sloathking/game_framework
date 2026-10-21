//
// Created by sloath on 10/15/26.
//

#ifndef SPRITECOMPONENT2D_H
#define SPRITECOMPONENT2D_H

#include "Component.h"
#include "Math.h"
#include <SDL3_image/SDL_image.h>
#include <unordered_map>

class SpriteComponent2D : public Component
{
public:
    enum AnchorPoint { TopLeft = 0, TopCenter = 1, TopRight = 2, CenterLeft = 3, CenterCenter = 4, CenterRight = 5, BottomLeft = 6, BottomCenter = 7, BottomRight = 8 };

    // symbolic constant
    static constexpr float kOriginalSize = -1.0f;

    explicit SpriteComponent2D(class Actor2D* owner, int drawOrder = 100);
    ~SpriteComponent2D() override;

    virtual void Draw(SDL_Renderer* renderer);

    virtual void SetTexture(SDL_Texture* texture);

    [[nodiscard]] bool GetVisibility() const { return mIsVisible; }
    void SetVisibility(const bool visible) { mIsVisible = visible; }

    [[nodiscard]] int GetDrawOder() const { return mDrawOrder; }

    [[nodiscard]] int GetTexWidth() const { return mTexWidth; }

    [[nodiscard]] int GetTexHeight() const { return mTexHeight; }

     [[nodiscard]] Vector2 GetOffset() const { return mOffset;}
    void SetOffset(const Vector2 vec) { mOffset = vec; }

    void SetClip(const SDL_FRect rect) { mClip = rect; }

    [[nodiscard]] SDL_FlipMode GetFlipMode() const { return mSpriteFlipMode; }
    void SetFlipMode(const SDL_FlipMode flip) { mSpriteFlipMode = flip; }

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
    int mTexWidth{0};
    int mTexHeight{0};

    Vector2 mOffset{Vector2::Zero};

    SDL_FRect mClip;

    SDL_FlipMode mSpriteFlipMode{SDL_FLIP_NONE};

    SDL_FPoint mCenter{ .x = 0.0f, .y = 0.0f };

    AnchorPoint mAnchor{ TopLeft };
    AnchorPoint mRotPoint{ TopLeft };

};

#endif //SPRITECOMPONENT2D_H
