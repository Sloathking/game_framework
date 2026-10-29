//
// Created by sloath on 10/28/26.
//

#ifndef FONT_H
#define FONT_H

#include "Math.h"
#include <string>
#include <unordered_map>
#include <SDL3_ttf/SDL_ttf.h>

class Font
{
public:
    explicit Font(class Engine* game);
    ~Font();

    // load/unload from a file
    bool Load(const std::string& fileName);
    void Unload() const;

    // give string and this font, draw to a texture
    SDL_Texture* RenderText(const std::string& text, const Vector3& color, float pointSize = 30.f);

private:
    Engine* mGame;

    // map of point sizes to font data
    std::unordered_map<float, TTF_Font*> mFontData;
};

#endif // FONT_H
