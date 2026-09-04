//
// Created by sloath on 03-Sep-26.
//

#ifndef GAME_H
#define GAME_H

#include <Engine/include/Engine.h>

class Game : public Engine
{
public:
    Game();
    ~Game() override;

protected:
    void LoadData() override;
    void UnloadData() override;

private:
    // shaders


};


#endif //GAME_H
