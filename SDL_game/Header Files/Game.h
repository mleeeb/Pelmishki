#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>

#include "Enemy.h"

class Game
{
public:
    Game();
    ~Game();

    SDL_AppResult SDL_AppInit();
    SDL_AppResult SDL_AppEvent(SDL_Event* event);
    SDL_AppResult SDL_AppIterate();
    void SDL_AppQuit(SDL_AppResult result);

    void SetWindowAndRenderer(SDL_Window* win, SDL_Renderer* ren) {
        window = win;
        renderer = ren;
    }

    SDL_FRect mainrect;

    // Константы для размеров окна
    static constexpr int SCREEN_WIDTH = 540;
    static constexpr int SCREEN_HEIGHT = 720;

private:
    void spawnEnemies();
    void checkVictory();
    void showVictoryScreen();
    void resetGame();
    bool isPointInRect(float x, float y, SDL_FRect rect);
    void activateNextEnemy();
    void loadBackground();

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

    std::vector<Enemy*> enemies;
    int currentEnemyIndex;
    bool gameActive;
    bool victoryScreen;

    SDL_Texture* victoryTexture;
    SDL_FRect victoryRect;

    SDL_Texture* backgroundTexture;
};