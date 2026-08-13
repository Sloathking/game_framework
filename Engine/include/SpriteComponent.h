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

    virtual void Draw(SDL_Renderer* renderer, const SDL_FRect* clip, float width, float height);

    virtual void SetTexture(SDL_Texture* texture);

    [[nodiscard]] int GetDrawOder() const { return mDrawOrder; }

    [[nodiscard]] int GetTexWidth() const { return mTexWidth; }

    [[nodiscard]] int GetTextHeight() const { return mTexHeight; }

     [[nodiscard]] Vector2 GetOffset() const { return Vector2(mXOffset, mYOffset);}
    void SetOffset(const float x, const float y) { mXOffset = x; mYOffset = y; }
    void SetOffset(const Vector2 vec) { mXOffset = vec.x; mYOffset = vec.y; }

    [[nodiscard]] double GetDegrees() const { return mDegrees; }
    void SetDegrees(const double degrees) { mDegrees = degrees; }

    [[nodiscard]] bool IsFlippedHorizontal() const { return flipHorizontal; }
    void SetFlipHorizontal(const bool flip) { flipHorizontal = flip; }

    [[nodiscard]] bool IsFlippedVertical() const { return flipVertical; }
    void SetFlipVertical(const bool flip) { flipVertical = flip; }

    [[nodiscard]] AnchorPoint GetAnchor() const { return mAnchor; }
    void SetAnchor(const AnchorPoint anchor)
    {
        mAnchor = anchor;
        anchorOffset = anchorOffsets[mAnchor];
    }

    [[nodiscard]] AnchorPoint GetRotPoint() const { return mRotPoint; }
    void SetRotPoint(const AnchorPoint rotPoint) { mRotPoint = rotPoint; }

protected:
    std::unordered_map<AnchorPoint, Vector2> anchorOffsets{
        { TopLeft, Vector2(0,0) },{ TopCenter, Vector2(-(mTexWidth * 0.5f),0) }, { TopRight, Vector2(-mTexWidth,0) },
    };
    Vector2 anchorOffset{0, 0 };

    SDL_Texture* mTexture{ nullptr };
    int mDrawOrder;
    int mTexWidth{ 0 };
    int mTexHeight{ 0 };

    float mXOffset{ 0.0 };
    float mYOffset{ 0.0 };

    double mDegrees{ 0.0 };

    bool flipHorizontal{ false };
    bool flipVertical{ false };

    AnchorPoint mAnchor{ TopLeft };
    AnchorPoint mRotPoint{ CenterCenter };

};

#endif //SPRITECOMPONENT_H
