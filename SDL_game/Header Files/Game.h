#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Player.h"

class Player;

class Game
{
public:
	Game();
	~Game();

	SDL_AppResult SDL_AppInit();
	SDL_AppResult SDL_AppEvent(SDL_Event* event);
	SDL_AppResult SDL_AppIterate();
	void SDL_AppQuit(SDL_AppResult result);

	SDL_FRect mainrect;

private:
	SDL_Window* window;
	SDL_Renderer* renderer;


	TTF_Font* font;

	Player* player;
};