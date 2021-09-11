#include <raylib.h>

#include "Game.hpp"

#define web

#if defined(web)
    #include <emscripten/emscripten.h>
#endif

Game* game;
void MainLoop(void);

int main(void)
{
    game = new Game();

#if defined(web)
    emscripten_set_main_loop(MainLoop, 0, 1);
#else
    SetTargetFPS(144);
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        game->StateSelect();
    }
#endif

    CloseWindow();

    return 0;
}

void MainLoop(void){
    game->StateSelect();
}