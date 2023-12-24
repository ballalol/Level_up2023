#include "game.h"
#include "init.h"

#include <curses.h>

void InitGame(GAME* game)
{
    if (game == nullptr) {
        return;
    }
    game->height = 0;
    game->width = 0;
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, true);

    getmaxyx(stdscr, game->height, game->width);
}
void DeinitGame(GAME *game)
{
    if (game == nullptr) {
        return;
    }
    endwin();
}
void StartGame(GAME *game)
{
    if (game == nullptr) {
        return;
    }
    printw("Start game");
    getch();
}
