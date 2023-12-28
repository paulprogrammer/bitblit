#include "main.h"
#include "log.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_video.h"

#include <stdio.h>
#include <unistd.h>

int main(int argc, char ** argv) {
    logger(DEBUG, "Starting");

    SDL_Window * win = SDL_CreateWindow("foo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320,200, SDL_WINDOW_SHOWN);
    if( win == NULL) {
        logger(ERROR, SDL_GetError());
    }

    SDL_Surface * windowSurface = SDL_GetWindowSurface(win);
    SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format,
                                                 0xFF, 0xFF, 0xFF));

    SDL_Delay(5000);

    SDL_DestroyWindow(win);
    SDL_Quit();

    logger( DEBUG, "Ending");
}