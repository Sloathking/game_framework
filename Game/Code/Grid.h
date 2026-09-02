//
// Created by sloath on 21-Aug-26.
//

#ifndef GRID_H
#define GRID_H

#include "../../Engine/include/Actor.h"
#include <vector>

class Grid : public Actor
{
public:
    explicit Grid(Game* game);

    void ProcessClick(int x, int y);

    bool FindPath(class Tile* start, Tile* goal) const;

    void BuildTower() const;

    [[nodiscard]] Tile* GetStartTile() const;
    [[nodiscard]] Tile* GetEndTile() const;

    void UpdateActor(float deltaTime) override;

    std::vector<Vector2> GetTilePositions();

private:
    void SelectTile(size_t row, size_t col);
    void UpdatePathTiles(const Tile* start) const;

    Tile* mSelectedTile{nullptr};

    std::vector<std::vector<Tile*>> mTiles;

    float mNextEnemyTimer{0.0f};

    const size_t NumRows{7};
    const size_t NumCols{16};

    const float StartY{192.0f};
    const float TileSize{64.0f};

    const float EnemyTime{1.5f};

};

#endif //GRID_H
