//
// Created by sloath on 03-Sep-26.
//

#ifndef GAME_H
#define GAME_H

#include <Engine/include/Engine.h>

typedef struct PositionTextureVertex
{
    float x, y, z;
    float u, v;
} PositionTextureVertex;

class Game : public Engine
{
public:
    Game();
    ~Game() override;


protected:
    void ProcessInput() override;

    void LoadData() override;
    void UnloadData() override;

private:

};


#endif //GAME_H
