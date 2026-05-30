#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "PlayerHUD.h"

class Player {
public:
	Player(SDL_Renderer* renderer, TTF_Font* font, int currentHealth, int totalHealth);
	~Player();

	void update();
	void draw();

private:
	SDL_Renderer* renderer;

	TTF_Font* font;

	PlayerHUD* playerHUD;

	//для стен

	int currentHealth;
	int totalHealth;
};