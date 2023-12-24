#ifndef GAME_H
#define GAME_H

struct GAME
{
    int width;
    int height;
};
void InitGame(GAME* game);

void DeinitGame(GAME *game);
void StartGame(GAME *game);
#endif // GAME_H
