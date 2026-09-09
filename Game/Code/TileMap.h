//
// Created by sloath on 12-Aug-26.
//

#ifndef TILEMAP_H
#define TILEMAP_H

#include <Engine/include/Actor2D.h>

class TileMap : public Actor2D
{
public:
    explicit TileMap(Engine* game);
    void UpdateActor(float deltaTime) override;

private:
    class TileMapComponent* mClosestTileMap;
    TileMapComponent* mMiddleTileMap;
    TileMapComponent* mFarthestTileMap;

};

#endif //TILEMAP_H
