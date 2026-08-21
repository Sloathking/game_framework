//
// Created by sloath on 21-Aug-26.
//

#include "Tile.h"
#include "../Engine/include/Game.h"
#include "../Engine/include/SpriteComponent.h"

Tile::Tile(Game* game) : Actor(game)
{
    mSpriteComp = new SpriteComponent(this);
    mSpriteComp->SetAnchor(SpriteComponent::CenterCenter);
    mSpriteComp->SetCenter(SpriteComponent::CenterCenter);
    UpdateTexture();
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
    mSpriteComp->SetTexture(GetGame()->GetTexture(text));
}
