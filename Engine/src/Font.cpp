//
// Created by sloath on 10/28/26.
//

#include "include/Font.h"
#include "include/Engine.h"
#include "include/Renderer2D.h"
#include <vector>

Font::Font(Engine* game) : mGame(game) {}

Font::~Font() = default;

// load/unload from a file
bool Font::Load(const std::string& fileName)
{
    // support these font sizes
    const std::vector<float> fontSize = {
        8, 9,
        10, 11, 12, 14, 16, 18,
        20, 22, 24, 26, 28,
        30, 32, 34, 36, 38,
        40, 42, 44, 46, 48,
        52, 56,
        60, 64, 68,
        72
    };

    // call TTF_OpenFont once per every font size
    for (const float& size : fontSize)
    {
        TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
        if (!font)
        {
            SDL_Log("Could not load %s in size %f! SDL Error: %s", fileName.c_str(), size, SDL_GetError());
            return false;
        }
        mFontData.emplace(size, font);
    }
    return true;
}

void Font::Unload() const
{
    for (auto& font : mFontData)
        TTF_CloseFont(font.second);
}

// give string and this font, draw to a texture
SDL_Texture* Font::RenderText(const std::string& text, const Vector3& color, const float pointSize)
{
    SDL_Texture* tex = nullptr;

    const auto it = mFontData.find(pointSize);
    if (it == mFontData.end())
    {
        SDL_Log("Point size %f is unsupported.", pointSize);
        return tex;
    }

    SDL_Color sdlColor;
    sdlColor.r = static_cast<Uint8>(color.x * 255);
    sdlColor.g = static_cast<Uint8>(color.y * 255);
    sdlColor.b = static_cast<Uint8>(color.z * 255);
    sdlColor.a = 255;

    TTF_Font* font = it->second;
    // const std::string& actualText = mGame->GetText(textKey);
    if (SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), text.length(), sdlColor))
    {
        // convert surface to texture
        tex = SDL_CreateTextureFromSurface(static_cast<Renderer2D*>(mGame->GetRenderer())->GetSDLRenderer(), surf);
        if (!tex) SDL_Log("Unable to create texture from rendered text! SDL Error: %s", SDL_GetError());
        SDL_DestroySurface(surf);
    }
    else
        SDL_Log("Unable to render text surface! SDL Error: %s", SDL_GetError());

    return tex;
}