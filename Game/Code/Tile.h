//
// Created by sloath on 21-Aug-26.
//

#ifndef TILE_H
#define TILE_H

#include "../../Engine/include/Actor.h"

class Tile : public Actor
{
public:
    friend class Grid;
    enum TileState
    {
        EDefault,
        EPath,
        EStart,
        EBase
    };

    explicit Tile(Game* game);

    [[nodiscard]] TileState GetTileState() const { return mTileState; }
    void SetTileState(TileState state);

    void ToggleSelect();

    [[nodiscard]] const Tile* GetParent() const { return mParent; }

private:
    void UpdateTexture() const;

    std::vector<Tile*> mAdjacent;

    Tile* mParent{nullptr};

    float f{0.0f};
    float g{0.0f};
    float h{0.0f};

    bool mInOpenSet{false};
    bool mInClosedSet{false};
    bool mBlocked{false};

    class SpriteComponent* mSpriteComp;

    TileState mTileState{EDefault};

    bool mSelected{false};
};


#endif //TILE_H
