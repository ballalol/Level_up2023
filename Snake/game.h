#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <thread>

enum MENU{
    START_GAME,
    RECORDS,
    EXIT
};

enum CURRENT_STATE{
    IN_SCREEN,
    IN_MENU,
    IN_GAME,
    IN_EXIT
};

enum GAME_COLOR{
    COLOR_SCREEN = 1,
    COLOR_MENU,
    COLOR_GAME,
    COLOR_SNAKE
};

struct GAME
{
    int width;
    int height;
    int current_state;
    int current_menu_option;
    std::thread* th;
};
void InitGame(GAME* game);

void DeinitGame(GAME *game);
void StartGame(GAME *game);
void GameStarter (GAME *game);

//для скрина
void ScreenKeyer(GAME *game, int cur);
void ScreenShower(GAME *game);
bool ScreenAction (GAME *game, std::chrono::milliseconds ms);

//для меню
void MenuKeyer(GAME *game, int cur);
void MenuShower(GAME *game);
bool MenuAction(GAME *game, std::chrono::milliseconds ms);

//для игры
void GameKeyer(GAME *game, int cur);
void GameShower(GAME *game);
bool GameAction(GAME *game, std::chrono::milliseconds ms);
#endif // GAME_H
