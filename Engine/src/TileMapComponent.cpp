//
// Created by sloath on 12-Aug-26.
//

#include "../include/TileMapComponent.h"

#include <iostream>
#include <charconv>

#include "../include/CSVUTils.h"
#include "../include/Actor.h"

TileMapComponent::TileMapComponent(Actor* owner, const int drawOrder) : SpriteComponent(owner, drawOrder)
{

}

void TileMapComponent::Update(const float deltaTime)
{

}

void TileMapComponent::Draw(SDL_Renderer* renderer, const SDL_FRect* clip, const float width, const float height)
{
    for (TileData& tile : mTiles)
    {
        SDL_FRect srcRect{ .x = mTileWidth * tile.spriteCoords.x, .y = mTileWidth * tile.spriteCoords.y, .w = mTileWidth, .h = mTileHeight };

        SDL_FRect dstRect{ .x = mOwner->GetPosition().x + mTileWidth * tile.xOffset, .y = mOwner->GetPosition().y + mTileHeight * tile.yOffset,
            .w = mTileWidth, .h = mTileHeight };

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

        SDL_FlipMode flipMode;
        if (flipHorizontal and flipVertical) flipMode = SDL_FLIP_HORIZONTAL_AND_VERTICAL;
        else flipMode = flipHorizontal ? SDL_FLIP_HORIZONTAL : flipVertical ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;

        SDL_FPoint anchor;
        anchor.x = rotOffsets[mRotPoint].x;
        anchor.y = rotOffsets[mRotPoint].y;

        //Render texture
        SDL_RenderTextureRotated(renderer, mTexture, &srcRect, &dstRect, mDegrees, &anchor, flipMode);
    }
}

void TileMapComponent::ReadFile(const std::string& fileName)
{
    mTiles.erase(mTiles.begin(), mTiles.end());
    int row = 0;
    for (std::ifstream file(fileName); auto& line : CSVRange(file))
    {
        int col = 0;
        for (int c = 0; c < line.size(); ++c)
        {
            TileData tile;
            const int num = stoi(line[c]);
            if (num == -1) continue;

            int yPos = num / mSpriteRows;
            int xPos = num % mSpriteRows;
            tile = TileData(col, row, Vector2(xPos, yPos));

            mTiles.emplace_back(tile);
            col++;
        }
        row++;
    }
}

void TileMapComponent::SetSpriteProperties(const int rows, const int cols, const float width, const float height)
{
    mSpriteRows = rows;
    mSpriteCols = cols;
    mTileWidth = width;
    mTileHeight = height;
}