#include <iostream>
#include <memory>

#include "game_of_life.h"

using namespace conway_game;

int main()
{
    game_of_life game;

    if (game.init())
    {
        game.run();
    }

    return 0;
}
