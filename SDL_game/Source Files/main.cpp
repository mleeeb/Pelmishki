#include <SDL3/SDL_main.h>
#include "Game.h"

Game game;

int main(int argc, char* argv[]) {
    if (game.SDL_AppInit() != SDL_APP_CONTINUE) {
        return -1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (game.SDL_AppEvent(&event) == SDL_APP_SUCCESS) {
                running = false;
                break;
            }
        }

        if (game.SDL_AppIterate() == SDL_APP_SUCCESS) {
            running = false;
        }

        SDL_Delay(16);
    }

    game.SDL_AppQuit(SDL_APP_CONTINUE);
    return 0;
}