#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>


static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_FRect strect = {0, 0, 200, 200};


//создание окошка
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("SDL3 Game", 1024, 900, 0, &window, &renderer);
	return SDL_APP_CONTINUE;
}


// отрисовка
SDL_AppResult SDL_AppIterate(void* appstate) {
	//создаём цвет
	SDL_SetRenderDrawColor(renderer, 86, 24, 89, 255);
	SDL_RenderClear(renderer);


	/* //отрисовка полого квадрата
	SDL_SetRenderDrawColor(renderer, 100, 30, 200, 255);
	SDL_FRect rectBorder = {400, 400, 100, 100};
	SDL_RenderRect(renderer, &rectBorder);


	// отрисовка квадрата
	SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
	SDL_FRect rect = {200, 200, 200, 200};
	SDL_RenderFillRect(renderer, &rect);


	//отрисовка линий
	SDL_RenderLine(renderer, 100, 100, 245, 121);
	//кривая
	SDL_FPoint lines[] = {
		{50, 50}, {100,600}, {561,800}
	};
	SDL_RenderLines(renderer, lines, SDL_arraysize(lines));

	//точка
	SDL_RenderPoint(renderer, 50, 36);*/

	//отрисовка текстуры
	SDL_Texture* stTexture = IMG_LoadTexture(renderer, "assets/cat.png");
	SDL_RenderTexture(renderer, stTexture, NULL, &strect);
	SDL_DestroyTexture(stTexture);
	

	SDL_RenderPresent(renderer);
	return SDL_APP_CONTINUE;
	
}



//нажатие клавиши
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	//если польз нажал на выход(крестик) - закрытие окна 
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}
	return SDL_APP_CONTINUE;
}

// как выходим
void SDL_AppQuit(void* appstate, SDL_AppResult) {

}