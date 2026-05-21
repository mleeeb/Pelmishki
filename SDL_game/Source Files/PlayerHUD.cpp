#include "PlayerHUD.h"

PlayerHUD::PlayerHUD(SDL_Renderer* renderer, TTF_Font* font):
	renderer(renderer),font(font),money(100)
{
	moneyText = std::to_string(money) + "$";
	SDL_Surface* moneySurface = TTF_RenderText_Solid(font, moneyText.c_str(), strlen(moneyText.c_str()), moneyColor);
	moneyTexture = SDL_CreateTextureFromSurface(renderer, moneySurface);
	WHmoneyText = {10, 10, 0, 0};
	SDL_GetTextureSize(moneyTexture, &WHmoneyText.w, &WHmoneyText.h);
	SDL_DestroySurface(moneySurface);
}

PlayerHUD::~PlayerHUD()
{
}


void PlayerHUD::update()
{
}

void PlayerHUD::draw()
{
	SDL_RenderTexture(renderer, moneyTexture, NULL, &WHmoneyText);
}