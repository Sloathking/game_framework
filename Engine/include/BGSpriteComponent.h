//
// Created by sloath on 06-Aug-26.
//

#ifndef CLION_GAME_PROGRAMMING_BGSPRITECOMPONENT_H
#define CLION_GAME_PROGRAMMING_BGSPRITECOMPONENT_H

#include "../include/SpriteComponent.h"
#include "../include/Math.h"
#include <vector>

class BGSpriteComponent : public SpriteComponent
{
public:
    BGSpriteComponent(class Actor* owner, int drawOrder = 10);

    // update draw override
    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;

    // set the texture used for the background
    void SetBGTextures(const std::vector<SDL_Texture*>& textures);

    // get / set the screen size and scroll speed
    void SetScreenSize(const Vector2& size) { mScreenSize = size; }
    void SetScrollSpeed(float scrollSpeed) { mScrollSpeed = scrollSpeed; }
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
    float mScrollSpeed;
};

#endif //CLION_GAME_PROGRAMMING_BGSPRITECOMPONENT_H
