#include "Enemy.h"
#include <cstdio>

Enemy::Enemy(SDL_Renderer* renderer, TTF_Font* font, int health, int level, int x, int y, const char* imagePath)
    : renderer(renderer), font(font), currentHealth(health), maxHealth(health), level(level), isActive(false) {

    float sizeW = 540.0f;
    float sizeH = 720.0f;
    rect = { static_cast<float>(x), static_cast<float>(y), sizeW, sizeH };
    texture = nullptr;
    enemyTexture = nullptr;

    if (imagePath) {
        loadTexture(imagePath);
    }

    if (!enemyTexture) {
        switch (level) {
        case 1: bgColor = { 139, 69, 19, 255 }; break;
        case 2: bgColor = { 178, 34, 34, 255 }; break;
        case 3: bgColor = { 75, 0, 130, 255 }; break;
        default: bgColor = { 100, 100, 100, 255 };
        }
    }

    updateText();
    SDL_Log("Enemy created: Level %d, Health %d/%d", level, currentHealth, maxHealth);
}

Enemy::~Enemy() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    if (enemyTexture) {
        SDL_DestroyTexture(enemyTexture);
    }
}

void Enemy::loadTexture(const char* imagePath) {
    SDL_Log("Loading texture: %s", imagePath);

    SDL_Texture* newTexture = IMG_LoadTexture(renderer, imagePath);
    if (newTexture) {
        float texW, texH;
        SDL_GetTextureSize(newTexture, &texW, &texH);
        SDL_Log("Texture loaded: %.0fx%.0f", texW, texH);

        // Растягиваем на весь экран 540x720
        rect.w = 540.0f;
        rect.h = 720.0f;
        rect.x = 0;
        rect.y = 0;

        enemyTexture = newTexture;
        SDL_Log("Texture scaled to full screen");
    }
    else {
        SDL_Log("Failed to load texture: %s", SDL_GetError());
        enemyTexture = nullptr;
    }
}

void Enemy::takeDamage(int damage) {
    if (!isActive) return;
    if (!isAlive()) return;

    currentHealth -= damage;
    if (currentHealth < 0) currentHealth = 0;
    updateText();
    SDL_Log("Damage taken! HP: %d/%d", currentHealth, maxHealth);
}

void Enemy::update() {
    // Можно добавить анимацию
}

void Enemy::draw() {
    if (!isActive) return;

    if (enemyTexture) {
        SDL_RenderTexture(renderer, enemyTexture, NULL, &rect);
    }
    else {
        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderFillRect(renderer, &rect);
    }

    // Жёлтая рамка
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderRect(renderer, &rect);

    // Текст уровня
    std::string levelText = "Level " + std::to_string(level);
    SDL_Surface* levelSurface = TTF_RenderText_Solid(font, levelText.c_str(), (int)levelText.length(), { 255, 255, 255, 255 });
    if (levelSurface) {
        SDL_Texture* levelTexture = SDL_CreateTextureFromSurface(renderer, levelSurface);
        if (levelTexture) {
            SDL_FRect levelDest;
            SDL_GetTextureSize(levelTexture, &levelDest.w, &levelDest.h);
            levelDest.x = (rect.w - levelDest.w) / 2;
            levelDest.y = 50;
            SDL_RenderTexture(renderer, levelTexture, NULL, &levelDest);
            SDL_DestroyTexture(levelTexture);
        }
        SDL_DestroySurface(levelSurface);
    }

    // Полоска здоровья внизу экрана
    float healthPercent = static_cast<float>(currentHealth) / maxHealth;

    SDL_FRect healthBarBg = { 20, rect.h - 80, rect.w - 40, 30 };
    SDL_FRect healthBar = { 20, rect.h - 80, (rect.w - 40) * healthPercent, 30 };

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &healthBarBg);

    if (healthPercent > 0.5f) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    }
    else if (healthPercent > 0.25f) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }
    SDL_RenderFillRect(renderer, &healthBar);

    // Текст здоровья
    if (texture) {
        destText.x = (rect.w - destText.w) / 2;
        destText.y = rect.h - 80 + (30 - destText.h) / 2;
        SDL_RenderTexture(renderer, texture, NULL, &destText);
    }
}

void Enemy::updateText() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    healthText = std::to_string(currentHealth) + "/" + std::to_string(maxHealth);
    SDL_Log("Updating health text: %s", healthText.c_str());

    SDL_Surface* surface = TTF_RenderText_Solid(font, healthText.c_str(), (int)healthText.length(), { 255, 255, 255, 255 });
    if (!surface) {
        SDL_Log("TTF_RenderText_Solid failed: %s", SDL_GetError());
        return;
    }

    SDL_Log("Surface created: w=%d, h=%d", surface->w, surface->h);

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("CreateTextureFromSurface failed: %s", SDL_GetError());
        SDL_DestroySurface(surface);
        return;
    }

    SDL_GetTextureSize(texture, &destText.w, &destText.h);
    SDL_Log("Texture created: w=%.0f, h=%.0f", destText.w, destText.h);

    SDL_DestroySurface(surface);
}