//
// Created by sloath on 06-Aug-26.
//

#ifndef BGSPRITECOMPONENT_H
#define BGSPRITECOMPONENT_H

#include "SpriteComponent2D.h"
#include "Math.h"
#include <vector>

class BGSpriteComponent : public SpriteComponent2D
{
public:
    explicit BGSpriteComponent(Actor2D* owner, int drawOrder = 10);

    // update draw override
    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer, Vector2 offset) override;

    // set the texture used for the background
    void SetBGTextures(const std::vector<SDL_Texture*>& textures);

    // get / set the screen size and scroll speed
    void SetScreenSize(const Vector2& size) { mScreenSize = size; }
    void SetScrollSpeed(const float scrollSpeed) { mScrollSpeed = scrollSpeed; }
    [[nodiscard]] float GetScrollSpeed() const { return mScrollSpeed; }

private:
    // struct to encapsulate each BG image and its offset
    struct BGTexture
    {
        SDL_Texture* mTexture{};
        Vector2 mOffset;
    };

    std::vector<BGTexture> mBGTextures;
    Vector2 mScreenSize;
    float mScrollSpeed{0.0f};
};

#endif //BGSPRITECOMPONENT_H
