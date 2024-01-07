#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <random>
#include <thread>
#include <vector>

enum MENU{
    START_GAME,
    RECORDS,
    EXIT
};

enum CURRENT_STATE{
    IN_SCREEN,
    IN_MENU,
    IN_GAME,
    IN_GAME_OVER,
    IN_RECORDS,
    IN_EXIT
};

enum GAME_COLOR{
    COLOR_SCREEN = 1,
    COLOR_MENU,
    COLOR_CHOICE,
    COLOR_GAME,
    COLOR_SNAKE,
    COLOR_APPLE,
};



struct GAME
{
    int width;
    int height;
    int current_state;
    int current_menu_option;
    int snake_step;
    int snake_speed;
    int apple_place;
    std::thread* th;
    const int Field_X = 50;
    const int Field_Y = 25;
};

struct SNAKE
{
    std::vector<char>Snake_Head;
    std::vector<char>Snake_Tail;
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
bool ApplePlace (GAME *game, int apple_placeX, int apple_placeY);

void AppleShower(GAME *game);
void SnakeMove(GAME *game, std::vector<char>Snake_Head, std::vector<char>Snake_Tail, int snake_step);
void SnakeGrow();
//****



#endif // GAME_H
