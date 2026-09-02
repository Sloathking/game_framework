//
// Created by sloath on 21-Aug-26.
//

#include "Grid.h"
#include "Tile.h"
#include "Tower.h"
#include "Enemy.h"

#include <algorithm>

Grid::Grid(Game* game) : Actor(game)
{
    // size tiles correctly
    mTiles.resize(NumRows);
    for (auto & mRow : mTiles)
        mRow.resize(NumCols);

    // create tiles
    for (size_t i = 0; i < mTiles.size(); ++i)
    {
        for (size_t j = 0; j < mTiles[i].size(); ++j)
        {
            mTiles[i][j] = new Tile(GetGame());
            mTiles[i][j]->SetPosition(Vector2(TileSize * 0.5f + j * TileSize, StartY + i * TileSize));
        }
    }

    // set start/end
    GetStartTile()->SetTileState(Tile::EStart);
    GetEndTile()->SetTileState(Tile::EBase);

    // set up adjacency lists
    for (size_t i = 0; i < NumRows; ++i)
    {
        for (size_t j = 0; j < NumCols; ++j)
        {
            if (i > 0)
                mTiles[i][j]->mAdjacent.push_back(mTiles[i - 1][j]);
            if (i < NumRows - 1)
                mTiles[i][j]->mAdjacent.push_back(mTiles[i + 1][j]);
            if (j > 0)
                mTiles[i][j]->mAdjacent.push_back(mTiles[i][j - 1]);
            if (j < NumCols - 1)
                mTiles[i][j]->mAdjacent.push_back(mTiles[i][j + 1]);
        }
    }

    FindPath(GetEndTile(), GetStartTile());
    UpdatePathTiles(GetStartTile());

    mNextEnemyTimer = EnemyTime;
}

void Grid::ProcessClick(int x, int y)
{
    y -= static_cast<int>(StartY - TileSize / 2);
    if (y >= 0)
    {
        x /= static_cast<int>(TileSize);
        y /= static_cast<int>(TileSize);
        if (x >= 0 and x < static_cast<int>(NumCols) and y >= 0 and y < static_cast<int>(NumCols))
            SelectTile(y, x);
    }
}

// implements A*, should be moved to an A* implementation class
bool Grid::FindPath(Tile* start, Tile* goal) const
{
    for (size_t i = 0; i < NumRows; ++i)
    {
        for (size_t j = 0; j < NumCols; ++j)
        {
            mTiles[i][j]->g = 0.0f;
            mTiles[i][j]->mInOpenSet = false;
            mTiles[i][j]->mInClosedSet = false;
        }
    }

    std::vector<Tile*> openSet;

    // set current node to start and add to closed set
    Tile* current = start;
    current->mInClosedSet = true;

    do
    {
        // add adjacent nodes to open set
        for (Tile* neighbor : current->mAdjacent)
        {
            if (neighbor->mBlocked) continue;

            // only check nodes that aren't in the closed set
            if (!neighbor->mInClosedSet)
            {
                if (!neighbor->mInOpenSet)
                {
                    // not in open, so set parent
                    neighbor->mParent = current;
                    neighbor->h = (neighbor->GetPosition() - goal->GetPosition()).Length();

                    // g(x) is the parent's g + cost of traversing edge
                    neighbor->g = current->g + TileSize;
                    neighbor->f = neighbor->g + neighbor->h;
                    openSet.emplace_back(neighbor);
                    neighbor->mInOpenSet = true;
                }
                else
                {
                    // compute g(x) cost if current becomes parent
                    if (const float newG = current->g + TileSize; newG < neighbor->g)
                    {
                        // adopt this node
                        neighbor->mParent = current;
                        neighbor->g = newG;
                        neighbor->f = neighbor->g + neighbor->h;
                    }
                }
            }
        }

        // if open set is empty, all possible paths are exhausted
        if (openSet.empty()) break;

        auto it = std::min_element(openSet.begin(), openSet.end(),
            [](const Tile* a, const Tile* b) { return a->f < b->f; });

        // set to current and move from open to closed
        current = *it;
        openSet.erase(it);
        current->mInOpenSet = false;
        current->mInClosedSet = true;
    } while ( current != goal);

    // did we find a path?
    return current == goal;
}

void Grid::BuildTower() const
{
    if (mSelectedTile and !mSelectedTile->mBlocked)
    {
        mSelectedTile->mBlocked = true;
        if (FindPath(GetEndTile(), GetStartTile()))
        {
            auto* t = new Tower(GetGame());
            t->SetPosition(mSelectedTile->GetPosition());
        }
        else
        {
            // tower would block the path, so don't allow build
            mSelectedTile->mBlocked = false;
            FindPath(GetEndTile(), GetStartTile());
        }
        UpdatePathTiles(GetStartTile());
    }
}

Tile* Grid::GetStartTile() const
{
    return mTiles[3][0];
}

Tile* Grid::GetEndTile() const
{
    return mTiles[3][15];
}

void Grid::UpdateActor(const float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    // is it time to spawn a new enemy?
    mNextEnemyTimer -= deltaTime;
    if (mNextEnemyTimer <= 0.0f)
    {
        new Enemy(GetGame());
        mNextEnemyTimer += EnemyTime;
    }
}

std::vector<Vector2> Grid::GetTilePositions()
{
    std::vector<Vector2> gridPos;
    for (int i = 0; i < mTiles.size(); ++i)
        for (int j = 0; j < mTiles[i].size(); ++j)
            gridPos.emplace_back(mTiles[i][j]->GetPosition());
    return gridPos;
}

void Grid::SelectTile(const size_t row, const size_t col)
{
    // make sure it's valid
    Tile::TileState tState = mTiles[row][col]->GetTileState();
    if (tState != Tile::EStart and tState != Tile::EDefault)
    {
        // deselect previous
        if (mSelectedTile) mSelectedTile->ToggleSelect();
        mSelectedTile = mTiles[row][col];
        mSelectedTile->ToggleSelect();
    }
}

void Grid::UpdatePathTiles(const Tile* start) const
{
    // reset all tiles to normal (except start/end);
    for (size_t i = 0; i < NumRows; ++i)
    {
        for (size_t j = 0; j < NumCols; ++j)
        {
            if (!(i == 3 and j == 0) and !(i == 3 and j == 15))
                mTiles[i][j]->SetTileState(Tile::EDefault);
        }
    }

    Tile* t = start->mParent;
    while (t != GetEndTile())
    {
        t->SetTileState(Tile::EPath);
        t = t->mParent;
    }
}
