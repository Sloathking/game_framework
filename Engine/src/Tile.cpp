//
// Created by sloath on 21-Aug-26.
//

#include "include/Tile.h"
#include "include/Engine.h"
#include "include/SpriteComponent2D.h"
#include "include/Renderer2D.h"
#include <string>

Tile::Tile(Engine* game) : Actor2D(game)
{
    mSpriteComp = new SpriteComponent2D(this);
    UpdateTexture();
}

void Tile::UpdateActor(float deltaTime)
{

}

void Tile::SetTileState(TileState state)
{
    mTileState = state;
    UpdateTexture();
}

void Tile::ToggleSelect()
{
    mSelected = !mSelected;
    UpdateTexture();
}

void Tile::UpdateTexture() const
{
    std::string text;
    switch (mTileState)
    {
    case EStart:
        text = "Assets/TileTan.png";
        break;
    case EBase:
        text = "Assets/TileGreen.png";
        break;
    case EPath:
        if (mSelected)
            text = "Assets/TileGreySelected.png";
        else
            text = "Assets/TileGrey.png";
        break;
    case EDefault:
    default:
        if (mSelected)
            text = "Assets/TileBrownSelected.png";
        else
            text = "Assets/TileBrown.png";
        break;
    }
    auto* renderer = dynamic_cast<Renderer2D*>(GetGame()->GetRenderer());
    mSpriteComp->SetTexture(renderer->GetTexture(text));
}
