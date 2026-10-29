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

private:
    class Cam2DActor* mCamActor;
    class HexGridActor* mHexGrid;

};

#endif //GAME_H
