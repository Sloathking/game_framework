#include <iostream>
#include "Game/Code/Game.h"

int main()
{
    std::cout << "Game in SDL" << std::endl;

    int exitCode{ 0 };

    Game game;
    if (!game.Initialize(ThreeD))
    {
        SDL_Log("Unable to initialize game!");
        exitCode = 1;
    }
    else
    {
        game.RunLoop();
    }

    game.Shutdown();

    return exitCode;
}