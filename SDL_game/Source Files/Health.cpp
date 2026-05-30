#include "Health.h"

Health::Health(SDL_Renderer* renderer, TTF_Font* font, int currentHealth, int totalHealth) :
	renderer(renderer),
	font(font),
	health(currentHealth),
	totalHealth(totalHealth)
{
	// 3 "плашки" на отрисовку хп
	destBorderHealthRect = { 10, 50, 300, 50 };
	destCurrentHealthRect = { 12, 52, 296, 46 };
	destTotalHealthRect = { 12, 52, 296, 46 };

	//рассчёт позиции текста
	float healthPercent = static_cast<float>(health) / totalHealth;
	SDL_Log("healthPercent: %.2f\n", healthPercent);
	destCurrentHealthRect.w = destCurrentHealthRect.w * healthPercent;

	updateText();
}

Health::~Health()
{
}

void Health::update()
{
}

void Health::draw()
{
	//отрисовка плашек
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &destBorderHealthRect);

	SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
	SDL_RenderFillRect(renderer, &destTotalHealthRect);

	SDL_SetRenderDrawColor(renderer, 235, 0, 0, 255);
	SDL_RenderFillRect(renderer, &destCurrentHealthRect);

	SDL_RenderTexture(renderer, texture, NULL, &destText);
}

void Health::updateText()
{
	//пишет сколько хп сейчас и общее кол-во
	text = std::to_string(health) + "/" + std::to_string(totalHealth);
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), strlen(text.c_str()), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_GetTextureSize(texture, &destText.w, &destText.h);

	destText.x = destBorderHealthRect.x + (destBorderHealthRect.w - destText.w) / 2;
	destText.y = destBorderHealthRect.y + (destBorderHealthRect.h - destText.h) / 2;
	SDL_DestroySurface(surface);
}