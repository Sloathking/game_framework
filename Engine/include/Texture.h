//
// Created by sloath on 12-Aug-26.
//

/* GET THIS IMPLEMENTED AND WORKING
 * Inject this between SpriteComponent and it's current SDL_Texture*
 * This is the sprite part of SpriteComponent
 * So needs to get added to textures vector
 * Is a component, so gets Game ref can do stuff with that.
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL3/SDL.h>
#include <string>

class Texture
{
public:
    //Symbolic constant
    static constexpr float kOriginalSize = -1.f;

    //Initializes texture variables
    explicit Texture();
    explicit Texture(class Game* game, const std::string& fileName);

    //Cleans up texture variables
    ~Texture();

    //Loads texture from disk
    bool LoadTexture(const Game* game, const std::string& path );

#if defined(SDL_TTF_MAJOR_VERSION)
    //Creates texture from text
    bool LoadFromRenderedText( std::string textureText, SDL_Color textColor );
#endif

    // Sets mTexture
    void SetTexture(SDL_Texture* texture) { mTexture = texture; }

    //Cleans up texture
    void Destroy();

    //Sets color modulation
    void SetColor( Uint8 r, Uint8 g, Uint8 b ) const;

    //Sets opacity
    void SetAlpha( Uint8 alpha ) const;

    //Sets blend mode
    void SetBlending( SDL_BlendMode blendMode ) const;

    //Draws texture
    void Draw(SDL_Renderer* renderer, float x, float y, const SDL_FRect* clip = nullptr,
        float width = kOriginalSize, float height = kOriginalSize, double degrees = 0.0,
        const SDL_FPoint* center = nullptr, SDL_FlipMode flipMode = SDL_FLIP_NONE ) const;

    //Gets texture attributes
    [[nodiscard]] int GetWidth() const { return mWidth; }
    [[nodiscard]] int GetHeight() const { return mHeight; }
    [[nodiscard]] bool IsLoaded() const { return mTexture != nullptr; }

private:
    //Contains texture data
    SDL_Texture* mTexture{ nullptr };

    //Texture dimensions
    int mWidth{ 0 };
    int mHeight{ 0 };

};

#endif //TEXTURE_H