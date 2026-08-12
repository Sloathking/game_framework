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

TileMapComponent::TileMapComponent(Actor* owner, const int drawOrder, const std::string& fileName) : SpriteComponent(owner, drawOrder)
{
    ReadFile(fileName);
}

void TileMapComponent::Update(const float deltaTime)
{

}

void TileMapComponent::Draw(SDL_Renderer* renderer)
{

}

void TileMapComponent::ReadFile(const std::string& fileName)
{
    for (std::ifstream file(fileName); auto& x : CSVRange(file))
    {
        std::vector<int> nums;
        //auto result = std::from_chars(row[0], row[row.size()]);
        for (int y = 0; y < x.size(); ++y)
        {
            nums.push_back(stoi(x[y]));
        }
        mTileNums.push_back(nums);
    }
}