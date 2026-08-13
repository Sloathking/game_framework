//
// Created by sloath on 12-Aug-26.
//

#include "../include/Texture.h"

#include <SDL3_image/SDL_image.h>
#include "../include/Constants.h"
#include "../include/Game.h"

Texture::Texture() = default;

Texture::Texture(Game* game, const std::string& fileName)
{
    mTexture = game->GetTexture(fileName);
    mWidth = mTexture->w;
    mHeight = mTexture->h;
}

Texture::~Texture()
{
    //Clean up texture
    Destroy();
}

bool Texture::LoadTexture(const Game* game, const std::string& path)
{
    //Clean up texture if it already exists
    Destroy();

    //Load surface
    if( SDL_Surface* loadedSurface = IMG_Load( path.c_str() ); loadedSurface == nullptr )
    {
        SDL_Log( "Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        //Color key image
        if( SDL_SetSurfaceColorKey( loadedSurface, true, SDL_MapSurfaceRGB( loadedSurface, 0x00, 0xFF, 0xFF ) ) == false )
        {
            SDL_Log( "Unable to color key! SDL error: %s", SDL_GetError() );
        }
        else
        {
            //Create texture from surface
            if( mTexture = SDL_CreateTextureFromSurface( game->GetRenderer(), loadedSurface ); mTexture == nullptr )
            {
                SDL_Log( "Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError() );
            }
            else
            {
                //Get image dimensions
                mWidth = loadedSurface->w;
                mHeight = loadedSurface->h;
            }
        }

        //Clean up loaded surface
        SDL_DestroySurface( loadedSurface );
    }

    //Return success if texture loaded
    return mTexture != nullptr;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::LoadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Clean up existing texture
    destroy();

    //Load text surface
    if( SDL_Surface* textSurface = TTF_RenderText_Blended( gFont, textureText.c_str(), 0, textColor ); textSurface == nullptr )
    {
        SDL_Log( "Unable to render text surface! SDL_ttf Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create texture from surface
        if( mTexture = SDL_CreateTextureFromSurface( mOwner->GetGame()->GetRenderer(), textSurface ); mTexture == nullptr )
        {
            SDL_Log( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Free temp surface
        SDL_DestroySurface( textSurface );
    }

    //Return success if texture loaded
    return mTexture != nullptr;
}
#endif

void Texture::Destroy()
{
    //Clean up texture
    SDL_DestroyTexture( mTexture );
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

void Texture::SetColor(const Uint8 r, const Uint8 g, const Uint8 b) const
{
    SDL_SetTextureColorMod( mTexture, r, g, b );
}

void Texture::SetAlpha(const Uint8 alpha ) const
{
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void Texture::SetBlending(const SDL_BlendMode blendMode ) const
{
    SDL_SetTextureBlendMode( mTexture, blendMode );
}

void Texture::Draw(SDL_Renderer* renderer, const float x, const float y, const SDL_FRect* clip,
    const float width, const float height, const double degrees,
    const SDL_FPoint* center, const SDL_FlipMode flipMode ) const
{
    //Set texture position
    SDL_FRect dstRect{ .x = x, .y = y, .w = static_cast<float>( mWidth ), .h = static_cast<float>( mHeight ) };

    //Default to clip dimensions if clip is given
    if( clip != nullptr )
    {
        dstRect.w = clip->w;
        dstRect.h = clip->h;
    }

    //Resize if new dimensions are given
    if( width > 0 )
    {
        dstRect.w = width;
    }
    if( height > 0 )
    {
        dstRect.h = height;
    }

    //Render texture
    SDL_RenderTextureRotated( renderer, mTexture, clip, &dstRect, degrees, center, flipMode );
}
