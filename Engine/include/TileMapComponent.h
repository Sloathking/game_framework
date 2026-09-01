//
// Created by sloath on 12-Aug-26.
//

#ifndef TILEMAPCOMPONENT_H
#define TILEMAPCOMPONENT_H

#include "../include/SpriteComponent.h"
#include <string>
#include <vector>

struct TileData
{
    int xOffset{0};
    int yOffset{0};
    Vector2 spriteCoords;
};

class TileMapComponent : public SpriteComponent
{
public:
    explicit TileMapComponent(Actor* owner, int drawOrder = 100);

    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer, Vector2 offset, const SDL_FRect* clip, float width, float height) override;

    // function to load and read in a tile map CSV file.
    void ReadFile(const std::string& fileName);

    // set all sprite sheet properties properties, i.e. number of rows, number of columns, individual tile width and height
    void SetSpriteProperties(int rows, int cols, float width, float height);

    int GetSpriteRows() const { return mSpriteRows; }
    void SetSpriteRows(const int num) { mSpriteRows = num; }

    int GetSpriteCols() const { return mSpriteCols; }
    void SetSpriteCols(const int num) { mSpriteCols = num; }

    float GetTileWidth() const { return mTileWidth; }
    void SetTileWidth(const float width) { mTileWidth = width; }

    float GetTileHeight() const { return mTileHeight; }
    void SetTileHeight(const float height) { mTileHeight = height; }

private:
    std::vector<TileData> mTiles;
    //std::vector<SpriteComponent*> mSprites;

    int mSpriteRows{0};
    int mSpriteCols{0};

    float mTileWidth{0.0};
    float mTileHeight{0.0};

};
/* CSV file that contains tile sprite data gets read in, contains single digit that is (x + y)
 *
 */
#endif //TILEMAPCOMPONENT_H