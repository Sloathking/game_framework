//
// Created by sloath on 12-Aug-26.
//

#ifndef TILEMAP_H
#define TILEMAP_H

#include "../Engine/include/Actor.h"


class TileMap : public Actor
{
public:
    explicit TileMap(Game* game);

private:
    class TileMapComponent* mClosestTileMap;
    TileMapComponent* mMiddleTileMap;
    TileMapComponent* mFarthestTileMap;

};


#endif //TILEMAP_H
