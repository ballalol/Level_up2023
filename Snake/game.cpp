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
    game->current_menu_option = MENU::START_GAME;
    game->th = new std::thread (GameStarter, game);
}
void InitColor()
{
    start_color();
    init_pair(COLOR_SCREEN, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_MENU, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOR_MENU, COLOR_WHITE, COLOR_GREEN);
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
        case CURRENT_STATE::IN_MENU:
            MenuKeyer(game, cur);
            break;
        case CURRENT_STATE::IN_GAME:
            GameKeyer(game, cur);
            break;
        }

    }
    while (game->current_state != IN_EXIT);
}
void ScreenKeyer(GAME *game, int cur){
    getch();
    game->current_state = CURRENT_STATE::IN_MENU;
}
void ScreenShower (GAME *game)
{
    if (game == nullptr) {
    return;
    }
    attron(COLOR_PAIR(COLOR_SCREEN));
    for(int i = 0; i < game->height; ++i){
        for(int j = 0; j < game->width; ++j){
            move(i,j);
            addch(' ');
        }
    }
    move(game->height / 3 - 1, game->width / 3 - 20);
    printw("   *****   **     **        *****  **    **  *******\n");
    move(game->height / 3 + 0, game->width / 3 - 20);
    printw("  **   **  ****   **      **   **  **   **   **     \n");
    move(game->height / 3 + 1, game->width / 3 - 20);
    printw("   **      ** **  **    ***    **  *****     **\n");
    move(game->height / 3 + 2, game->width / 3 - 20);
    printw("    **     **  ** **   ***     **  ******    *******\n");
    move(game->height / 3 + 3, game->width / 3 - 20);
    printw("     **    **   ****  ***********  **   **   **     \n");
    move(game->height / 3 + 4, game->width / 3 - 20);
    printw("  **   **  **    ***  ***      **  **    **  **     \n");
    move(game->height / 3 + 5, game->width / 3 - 20);
    printw("   ******  **     **  ***      **  **    **  *******\n");
    move(game->height / 3 + 6, game->width / 3 - 20);
    printw("of life\n");
    attroff(COLOR_PAIR(COLOR_SCREEN));
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
            break;
        case CURRENT_STATE::IN_MENU:
            changes = MenuAction(game, std::chrono::duration_cast < std::chrono::milliseconds > (diff));
            break;
        case CURRENT_STATE ::IN_GAME:
            changes = GameAction(game, std::chrono::duration_cast < std::chrono::milliseconds > (diff));
            break;
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
void MenuKeyer(GAME *game, int cur)
{
    switch (cur)
    {
    case 10: //enter
    {
        if(game->current_menu_option == MENU::START_GAME)
        {
            game->current_state = CURRENT_STATE::IN_GAME;
        }
        if(game->current_menu_option == MENU::EXIT)
        {
            game->current_state = CURRENT_STATE::IN_EXIT;
        }
        break;
    }
    case KEY_DOWN:
    {
        game->current_menu_option += 1;
        if (game->current_menu_option > EXIT) {
            game->current_menu_option = START_GAME;
        }
        break;
    }
    case KEY_UP:
    {
        game->current_menu_option -= 1;
        if (game->current_menu_option < START_GAME) {
            game->current_menu_option = EXIT;
        }
        break;
    }
    }
}
void MenuShower(GAME *game)
{
    if(game->current_menu_option == MENU::START_GAME){
        move(game->height / 2 - 1, game->width / 2 - 5);
        printw("* Start game *\n");
        move(game->height / 2 + 0, game->width / 2 - 5);
        printw("  Records  \n");
        move(game->height / 2 + 1, game->width / 2 - 5);
        printw("  Exit  \n");

    }
    if(game->current_menu_option == MENU::RECORDS){
        move(game->height / 2 - 1, game->width / 2 - 5);
        printw("  Start game  \n");
        move(game->height / 2 + 0, game->width / 2 - 5);
        printw("* Records *\n");
        move(game->height / 2 + 1, game->width / 2 - 5);
        printw("  Exit  \n");

    }
    if(game->current_menu_option == MENU::EXIT){
        move(game->height / 2 - 1, game->width / 2 - 5);
        printw("  Start game  \n");
        move(game->height / 2 + 0, game->width / 2 - 5);
        printw("  Records  \n");
        move(game->height / 2 + 1, game->width / 2 - 5);
        printw("* Exit *\n");

    }
}
bool MenuAction(GAME *game, std::chrono::milliseconds ms)
{
    if(ms.count() > 30){
        clear();
        attron(COLOR_PAIR(COLOR_MENU));
        MenuShower(game);
        attroff(COLOR_PAIR(COLOR_MENU));
        refresh();
        return true;
    }
    return false;
}
void GameKeyer(GAME *game, int cur)
{
    switch (cur) {
    case 27: //esc
        game->current_state = CURRENT_STATE::IN_MENU;
        break;
    }
}
void GameShower(GAME *game)
{
    move(0,0);
    printw("+");
    move(52, 0);
    printw("+");
    for(int j = 0; j < 50; ++j){
        move(0, 1 + j);
        printw("----------+\n");
    }
    for(int i = 0; i < 25; ++i){
        move(1 + i, 0);
        printw("|                                                           |\n");
    }
    move(25,0);
    printw("+");
    move(52, 0);
    printw("+");
    for(int j = 0; j < 50; ++j){
        move(25, 1 + j);
        printw("----------+\n");
    }
    move(0, 60);
    printw("+-----------+");
    move(1,64);
    printw("Score   |");
    move(2, 60);
    printw("+-----------+");
    move(3, 60);
    printw("|           |");
    move(4, 60);
    printw("+-----------+");
}
bool GameAction(GAME *game, std::chrono::milliseconds ms)
{
    if(ms.count() > 30){
        clear();
        GameShower(game);
        refresh();
        return true;
    }
    return false;
}
