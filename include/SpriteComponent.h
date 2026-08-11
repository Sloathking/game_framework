//
// Created by sloath on 06-Aug-26.
//

#ifndef CLION_GAME_PROGRAMMING_SPRITECOMPONENT_H
#define CLION_GAME_PROGRAMMING_SPRITECOMPONENT_H

#include "Component.h"
#include <SDL3_image/SDL_image.h>

class SpriteComponent : public Component
{
public:
    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(SDL_Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture);

    int GetDrawOder() const { return mDrawOrder; }
    int GetTexWidth() const { return mTexWidth; }
    int GetTextHeight() const { return mTexHeight; }

protected:
    SDL_Texture* mTexture;
    int mDrawOrder;
    int mTexWidth;
    int mTexHeight;
};

#endif //CLION_GAME_PROGRAMMING_SPRITECOMPONENT_H
