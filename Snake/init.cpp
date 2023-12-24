#include "init.h"
#include <curses.h>

void Init(GAME* game)
{
    if (game){
        return;
    }
    initscr();
    int row, col;
    getmaxyx (stdscr, game->height, game->width);
}
void Deinit()
{
    endwin();
}
