//
// Created by sloath on 12-Aug-26.
//

#ifndef TILEMAPCOMPONENT_H
#define TILEMAPCOMPONENT_H
#include <string>

#include "../include/SpriteComponent.h"
#include <vector>

class TileMapComponent : public SpriteComponent
{
public:
    explicit TileMapComponent(Actor* owner, int drawOrder = 100);
    TileMapComponent(Actor* owner, int drawOrder, const std::string& fileName);

    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer, const SDL_FRect* clip, float width, float height) override;

    // function to load and read in a tile map CSV file.
    void ReadFile(const std::string& fileName);

private:
    std::vector<std::vector<int>> mTileNums;
    std::vector<std::vector<SpriteComponent>> mSprites;

};


#endif //TILEMAPCOMPONENT_H
