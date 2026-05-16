#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

SDL_AppResult Game::SDL_AppInit()
{
	//окно
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("SDL3 Game", 1024, 900, 0, &window, &renderer);
	return SDL_AppResult();
}

SDL_AppResult Game::SDL_AppEvent(SDL_Event* event)
{
	switch (event->type) {
	case SDL_EVENT_QUIT:
		return SDL_APP_SUCCESS;
		break;
	default:
		break;
	}
	return SDL_APP_CONTINUE;
}

SDL_AppResult Game::SDL_AppIterate()
{
	//создаём цвет
	SDL_SetRenderDrawColor(renderer, 86, 24, 89, 255);
	SDL_RenderClear(renderer);


	SDL_RenderPresent(renderer);
	return SDL_APP_CONTINUE;
}

void Game::SDL_AppQuit(SDL_AppResult result)
{
}