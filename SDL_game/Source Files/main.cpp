#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>

#include "Game.h"


Game game;


// окошко
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	return game.SDL_AppInit();
}


// отрисовка
SDL_AppResult SDL_AppIterate(void* appstate) {
	return game.SDL_AppIterate();
}



//нажатие клавиши
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	return game.SDL_AppEvent(event);
}

// как выходим
void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	game.SDL_AppQuit(result);
}