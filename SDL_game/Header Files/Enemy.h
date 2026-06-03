#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class Enemy {
public:
    Enemy(SDL_Renderer* renderer, TTF_Font* font, int health, int level, int x, int y, const char* imagePath = nullptr);
    ~Enemy();

    void update();
    void draw();
    void takeDamage(int damage);
    bool isAlive() const { return currentHealth > 0; }
    int getHealth() const { return currentHealth; }
    SDL_FRect getRect() const { return rect; }
    int getLevel() const { return level; }
    void setActive(bool active) { isActive = active; }
    bool getActive() const { return isActive; }

private:
    void updateText();
    void loadTexture(const char* imagePath);

    SDL_Renderer* renderer;
    TTF_Font* font;

    int currentHealth;
    int maxHealth;
    int level;
    SDL_FRect rect;
    bool isActive;

    std::string healthText;
    SDL_Texture* texture;
    SDL_Texture* enemyTexture;
    SDL_FRect destText;
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Color bgColor;
};