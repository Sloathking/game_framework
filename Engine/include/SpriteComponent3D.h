//
// Created by sloath on 06-Aug-26.
//
// figure out anchor point stuff
#ifndef SPRITECOMPONENT3D_H
#define SPRITECOMPONENT3D_H

#include "Component.h"
#include "Math.h"
#include <SDL3_image/SDL_image.h>
#include <unordered_map>

class SpriteComponent3D : public Component
{
public:
    explicit SpriteComponent3D(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent3D() override;

    virtual void Draw(class Shader* shader);

    virtual void SetTexture(class Texture* texture);

    [[nodiscard]] bool GetVisibility() const { return mIsVisible; }
    void SetVisibility(const bool visible) { mIsVisible = visible; }

    [[nodiscard]] int GetDrawOder() const { return mDrawOrder; }

    [[nodiscard]] int GetTexWidth() const { return mTexWidth; }

    [[nodiscard]] int GetTextHeight() const { return mTexHeight; }

    [[nodiscard]] double GetRotation() const { return mRotation; }
    void SetRotation(const float rotation) { mRotation = rotation; }

protected:
    bool mIsVisible{true};

    Texture* mTexture{ nullptr };
    int mDrawOrder;
    int mTexWidth{ 0 };
    int mTexHeight{ 0 };

    float mRotation{ 0.0 };
};

#endif //SPRITECOMPONENT3D_H
