//
// Created by sloath on 12-Aug-26.
//

/* GET THIS IMPLEMENTED AND WORKING
 * Inject this between SpriteComponent and it's current SDL_Texture*
 * This get's the SDL_Texture and sprite component
 * So needs to get added to textures vector
 * Is a component, so gets Game ref can do stuff with that.
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include "../include/Component.h"

#include <SDL3/SDL.h>
#include <string>

class Texture : public Component
{
public:
    //Symbolic constant
    static constexpr float kOriginalSize = -1.f;

    //Initializes texture variables
    explicit Texture(class Actor* owner, int updateOrder = 100);

    //Cleans up texture variables
    ~Texture() override;

    //Loads texture from disk
    bool LoadFromFile( const std::string& path );

#if defined(SDL_TTF_MAJOR_VERSION)
    //Creates texture from text
    bool LoadFromRenderedText( std::string textureText, SDL_Color textColor );
#endif

    //Cleans up texture
    void Destroy();

    //Sets color modulation
    void SetColor( Uint8 r, Uint8 g, Uint8 b );

    //Sets opacity
    void SetAlpha( Uint8 alpha );

    //Sets blend mode
    void SetBlending( SDL_BlendMode blendMode );

    //Draws texture
    void Draw( float x, float y, SDL_FRect* clip = nullptr, float width = kOriginalSize, float height = kOriginalSize, double degrees = 0.0, SDL_FPoint* center = nullptr, SDL_FlipMode flipMode = SDL_FLIP_NONE );

    //Gets texture attributes
    [[nodiscard]] int GetWidth() const { return mWidth; }
    [[nodiscard]] int GetHeight() const { return mHeight; }
    [[nodiscard]] bool IsLoaded() const { return mTexture != nullptr; }

private:
    //Contains texture data
    SDL_Texture* mTexture{};

    //Texture dimensions
    int mWidth{ 0 };
    int mHeight{ 0 };

};


#endif //TEXTURE_H
