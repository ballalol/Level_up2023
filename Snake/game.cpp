#include "game.h"
#include "init.h"

#include <chrono>
#include <curses.h>
#include <stdlib.h>
#include <time.h>

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
    game->current_state = CURRENT_STATE::IN_SCREEN;
    game->th = new std::thread (GameStarter, game);
}
void DeinitGame(GAME *game)
{
    if (game == nullptr) {
        return;
    }
    if (game->th && game->th->joinable())
    {
        game->th->join();
    }

    delete game->th;
    endwin();
}
void StartGame(GAME *game)
{
    if (game == nullptr) {
        return;
    }
    int cur;
    do {
        cur = getch();
        switch (game->current_state) {
        case CURRENT_STATE::IN_SCREEN:
            ScreenKeyer(game, cur);
            break;
        }
    }
    while (game->current_state != IN_EXIT);
}
void ScreenKeyer(GAME *game, int cur){
    getch();
    game->current_state = CURRENT_STATE::IN_EXIT;
}
void ScreenShower (GAME *game)
{
    printw("SNAKE");
}
void GameStarter (GAME *game)
{
    if (game == nullptr) {
        return;
    }
    auto begin = std::chrono::steady_clock::now();
    while (game->current_state != CURRENT_STATE::IN_EXIT) {
        const auto now = std::chrono::steady_clock::now();
        const auto diff = now - begin;
        bool changes = false;
        switch (game->current_state) {
        case CURRENT_STATE::IN_SCREEN:
            changes = ScreenAction(game, std::chrono::duration_cast < std::chrono::milliseconds > (diff));

        }

    }
}
bool ScreenAction (GAME *game, std::chrono::milliseconds ms)
{
    if(ms.count() > 30){
        clear();
        ScreenShower(game);
        refresh();
        return true;
    }
    return false;
}
