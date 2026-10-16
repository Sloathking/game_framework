//
// Created by sloath on 10/15/26.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>

class Renderer {
public:
    explicit Renderer(class Engine* game) : mGame(game) {}
    virtual ~Renderer() = default;
    virtual bool Initialize(float screenWidth, float screenHeight) = 0;
    virtual void Shutdown() = 0;
    virtual void Draw() const = 0;

    [[nodiscard]] SDL_Window* GetWindow() const { return mWindow; }

protected:
    SDL_Window* mWindow{nullptr};
    Engine* mGame{nullptr};

private:

};

#endif //RENDERER_H
