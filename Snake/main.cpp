#include "game.h"
#include "init.h"
#include <curses.h>

int main()
{
    GAME game;

    InitGame(&game);
    StartGame(&game);
    DeinitGame(&game);



    return 0;
}
