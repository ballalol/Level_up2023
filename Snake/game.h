#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <thread>

enum CURRENT_STATE{
    IN_SCREEN,
    IN_MENU,
    IN_GAME,
    IN_EXIT
};

struct GAME
{
    int width;
    int height;
    int current_state;
    std::thread* th;
};
void InitGame(GAME* game);

void DeinitGame(GAME *game);
void StartGame(GAME *game);
void ScreenKeyer(GAME *game, int cur);
void ScreenShower(GAME *game);
void GameStarter (GAME *game);
bool ScreenAction (GAME *game, std::chrono::milliseconds ms);
#endif // GAME_H
