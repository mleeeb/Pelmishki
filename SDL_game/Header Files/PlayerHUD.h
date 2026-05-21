#pragma once
#include <string>
#include <SDL3/SDL.h>

#include <SDL3_ttf/SDL_ttf.h>

class PlayerHUD
{
public:
	PlayerHUD(SDL_Renderer* renderer, TTF_Font* font);
	~PlayerHUD();

	void update();
	void draw();


private:
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Texture* moneyTexture;
	int money;
	std::string moneyText;
	SDL_Color moneyColor = {255, 255, 255, 255};
	SDL_FRect WHmoneyText;
};