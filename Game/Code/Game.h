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
    void ProcessInput() override;
    bool ProcessGameEvent(SDL_Event* event) override;

    void LoadData() override;
    void UnloadData() override;

    class Cam2DActor* mCamActor;

    int asteroidCount{0};

    class HexGridActor* mHexGrid;

private:

};

#endif //GAME_H
