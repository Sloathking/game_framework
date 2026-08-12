//
// Created by sloath on 12-Aug-26.
//

#include "../include/TileMap.h"

#include "../include/Game.h"
#include "../include/TileMapComponent.h"

TileMap::TileMap(Game* game) : Actor(game)
{
    mClosestTileMap = new TileMapComponent(this);
    mClosestTileMap->SetTexture(game->GetTexture("../../Game/Assets/tiles.png"));

    const std::string fileName{"../../Game/Assets/MapLayer1.csv"};
    mClosestTileMap->ReadFile(fileName);
}