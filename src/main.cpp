#include <raylib.h>

#include "Game.hpp"

int main(void)
{
    Game game = Game();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        game.StateSelect();
    }

    CloseWindow();

    return 0;
}