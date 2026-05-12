#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>


static SDL_Window* window;
static SDL_Renderer* renderer;


//создание окошка
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("SDL3 Game", 800, 640, 0, &window, &renderer);
	return SDL_APP_CONTINUE;
}


// отрисовка
SDL_AppResult SDL_AppIterate(void* appstate) {
	//создаём цвет
	SDL_SetRenderDrawColor(renderer, 86, 24, 89, 255);
	SDL_RenderClear(renderer);


	// отрисовка полого квадрата
	SDL_SetRenderDrawColor(renderer, 100, 30, 200, 255);
	SDL_FRect rectBorder;
	rectBorder.x = 400;
	rectBorder.y = 400;
	rectBorder.w = 100;
	rectBorder.h = 100;
	SDL_RenderRect(renderer, &rectBorder);


	// отрисовка квадрата
	SDL_SetRenderDrawColor(renderer, 100, 30, 200, 255);
	SDL_FRect rect;
	rect.x = 200;
	rect.y = 200;
	rect.w = 200;
	rect.h = 200;
	SDL_RenderFillRect(renderer, &rect);


	//отрисовка линий
	SDL_RenderLine(renderer, 100, 100, 245, 121);
	//кривая
	SDL_FPoint lines[] = {
		{50, 50}, {100,600}, {561,800}
	};
	SDL_RenderLines(renderer, lines, SDL_arraysize(lines));

	//точка
	SDL_RenderPoint(renderer, 50, 36);

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