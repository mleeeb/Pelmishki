#include "Game.h"
#include <iostream>

Game::Game()
{
	mainrect = { 0, 0, 1280, 720};

	player = nullptr;

}

Game::~Game()
{
}

SDL_AppResult Game::SDL_AppInit()
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	//окно
	SDL_CreateWindowAndRenderer("SDL3 Game", 1280, 720, 0, &window, &renderer);
	//подключение шрифта
	font = TTF_OpenFont("C:/Users/1991/source/repos/Pelmishki/SDL_game/Resourses/assets/Fonts/Font_HTR.ttf", 24);


	player = new Player(renderer, font, 50, 100);

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
	//создаём окрас
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
	SDL_RenderClear(renderer);

	// отрисовка изображения
	SDL_Texture* background = IMG_LoadTexture(renderer, "c:/users/1991/source/repos/pelmishki/sdl_game/resourses/assets/main.jpg");
	SDL_RenderTexture(renderer, background, NULL, &mainrect);
	SDL_DestroyTexture(background);

	if (player) {
		player->update();
		player->draw();
	}

	SDL_RenderPresent(renderer);
	return SDL_APP_CONTINUE;
}

void Game::SDL_AppQuit(SDL_AppResult result)
{
}