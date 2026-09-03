//
// Created by sloath on 12-Aug-26.
//

#include "TileMap.h"

#include "../../Engine/include/Engine.h"
#include "../../Engine/include/TileMapComponent.h"

TileMap::TileMap(Engine* game) : Actor(game)
{
    mClosestTileMap = new TileMapComponent(this, 30);
    mClosestTileMap->SetTexture(game->GetTexture("Assets/Tiles.png"));
    mClosestTileMap->SetAnchor(SpriteComponent::AnchorPoint::TopLeft);
    mClosestTileMap->SetSpriteProperties(8, 24, 32, 32);

    mMiddleTileMap = new TileMapComponent(this, 20);
    mMiddleTileMap->SetTexture(game->GetTexture("Assets/Tiles.png"));
    mMiddleTileMap->SetAnchor(SpriteComponent::AnchorPoint::TopLeft);
    mMiddleTileMap->SetSpriteProperties(8, 24, 32, 32);

    mFarthestTileMap = new TileMapComponent(this, 10);
    mFarthestTileMap->SetTexture(game->GetTexture("Assets/Tiles.png"));
    mFarthestTileMap->SetAnchor(SpriteComponent::AnchorPoint::TopLeft);
    mFarthestTileMap->SetSpriteProperties(8, 24, 32, 32);

    std::string fileName{"../../Game/Assets/MapLayer1.csv"};
    mClosestTileMap->ReadFile(fileName);

    fileName = "../../Game/Assets/MapLayer2.csv";
    mMiddleTileMap->ReadFile(fileName);

    fileName = "../../Game/Assets/MapLayer3.csv";
    mFarthestTileMap->ReadFile(fileName);
}