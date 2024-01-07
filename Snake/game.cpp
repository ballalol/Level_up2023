#include "game.h"
#include "init.h"

#include <chrono>
#include <curses.h>
#include <random>
#include <stdlib.h>
#include <time.h>

void InitColor()
{
    start_color();
    init_pair(COLOR_SCREEN, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_MENU, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOR_GAME, COLOR_WHITE, COLOR_GREEN);
    init_pair(COLOR_CHOICE, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_APPLE, COLOR_RED, COLOR_GAME);
}
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

    game->snake_speed = 1;
    InitColor();
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
    attroff(COLOR_PAIR(COLOR_SCREEN));
    move(25, 40);
    attrset(A_UNDERLINE);
    printw("PRESS ANY KEY");
    attroff(A_UNDERLINE);
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
        attron(COLOR_PAIR(COLOR_CHOICE));
        move(game->height / 2 - 1, game->width / 2 - 5);
        printw("* Start game *\n");
        attroff(COLOR_PAIR(COLOR_CHOICE));
        attron(COLOR_PAIR(COLOR_MENU));
        move(game->height / 2 + 0, game->width / 2 - 5);
        printw("  Records  \n");
        move(game->height / 2 + 1, game->width / 2 - 5);
        printw("  Exit  \n");
        attroff(COLOR_PAIR(COLOR_MENU));

    }
    if(game->current_menu_option == MENU::RECORDS){
        attron(COLOR_PAIR(COLOR_MENU));
        move(game->height / 2 - 1, game->width / 2 - 5);
        printw("  Start game  \n");
        move(game->height / 2 + 0, game->width / 2 - 5);
        attron(COLOR_PAIR(COLOR_CHOICE));
        printw("* Records *\n");
        attroff(COLOR_PAIR(COLOR_CHOICE));
        attron(COLOR_PAIR(COLOR_MENU));
        move(game->height / 2 + 1, game->width / 2 - 5);
        printw("  Exit  \n");
        attroff(COLOR_PAIR(COLOR_MENU));

    }
    if(game->current_menu_option == MENU::EXIT){
        attron(COLOR_PAIR(COLOR_MENU));
        move(game->height / 2 - 1, game->width / 2 - 5);
        printw("  Start game  \n");
        move(game->height / 2 + 0, game->width / 2 - 5);
        printw("  Records  \n");
        move(game->height / 2 + 1, game->width / 2 - 5);
        attron(COLOR_PAIR(COLOR_CHOICE));
        printw("* Exit *\n");
        attroff(COLOR_PAIR(COLOR_CHOICE));
        attroff(COLOR_PAIR(COLOR_MENU));

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
        {
            game->current_state = CURRENT_STATE::IN_MENU;
            break;
        }
    }
}
void GameShower(GAME *game)
{
    const int Field_X = 50;
    const int Field_Y = 25;
    int Field [Field_Y][Field_X] = {};
    for(int i = 0; i < Field_Y; ++i){
        for(int j = 0; j < Field_X; ++j){
            mvaddch(i, j, 'x');
        }
    }
    for(int i = 1; i < Field_Y - 1; ++i){
        for(int j = 1; j < Field_X - 1; ++j){
            attron(A_DIM | COLOR_PAIR(COLOR_GAME));
            mvaddch(i, j, ' ');
            attroff(A_DIM | COLOR_PAIR(COLOR_GAME));
        }
    }
    //поле для счета
    move(0,60);
    printw("+-----------+");
    move(1,60);
    printw("|   Score   |");
    move(2, 60);
    printw("+-----------+");
    move(3, 60);
    printw("|           |");
    move(4, 60);
    printw("+-----------+");
    //for(int Snake_Head_Y = 0; Snake_Head_Y < 25; ++Snake_Head_Y){
    //for(int Snake_Head_X = 0; Snake_Head_X < 50; ++Snake_Head_X){
    //move(Field[Snake_Head_Y][Snake_Head_Y]);
    //printw("#");
    //int apple_place;
    //Field[apple_place] = rand() % Field[25][50];
    //move(Field[apple_place]);
    //printw("@");
    //      }
    //  }
    int Apple_Y;
    int Apple_X;
    srand(time(NULL));
    bool Apple_Place = false;
    if (!Apple_Place){
        do
        {
        Apple_Y = rand() % Field_Y;
        Apple_X = rand() % Field_X;
        }while(Field[Apple_Y][Apple_X] == 'x'); //&& Field[Apple_Y][Apple_X] == ' ');
        Apple_Place = 1;
    }
    attron(A_BOLD | COLOR_PAIR(COLOR_APPLE));
    mvaddch(Apple_Y, Apple_X, '@');
    attroff(A_BOLD | COLOR_PAIR(COLOR_APPLE));
}


void AppleShower(GAME *game)
{
char Apple = '@';
for(int i = 0; i < 25; ++i){
        for(int j = 0; j < 50; ++j){
            double apple_placeY = rand() % i;
            double apple_placeX = rand () % j;
            move(apple_placeX, apple_placeY);
            printw("%c",Apple);
        }
    }
}
//printw("%c", Snake_Tail);

void SnakeMove(GAME *game, std::vector<char>Snake_Head, std::vector<char>Snake_Tail, int snake_step)
{

    switch(snake_step)
    {
        case KEY_UP:
        {

            break;
        }
        case KEY_RIGHT:
        {

            break;
        }
        case KEY_DOWN:
        {

            break;
        }
        case KEY_LEFT:
        {
            //game->snake_move = ;
            break;
        }

    }
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



