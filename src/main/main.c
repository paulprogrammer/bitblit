#include "main.h"
#include "log.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_video.h"

#include <stdio.h>
#include <unistd.h>

int main(int argc, char ** argv) {
    logger(DEBUG, "Starting");

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * win = SDL_CreateWindow("foo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320,200, SDL_WINDOW_SHOWN);
    if( win == NULL) {
        logger(ERROR, SDL_GetError());
    }

    SDL_UpdateWindowSurface(win);

    SDL_Surface * windowSurface = SDL_GetWindowSurface(win);
    SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format,
                                                 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(win);

    SDL_Event e;
    int keep_open=1;
    while( keep_open) {
        while (SDL_PollEvent(&e) > 0) {
            switch(e.type)
            {
                case SDL_QUIT:
                    keep_open = 0;
                    break;
            }
            SDL_UpdateWindowSurface(win);
        }
    }

    SDL_DestroyWindowSurface( win);
    SDL_DestroyWindow(win);
    SDL_Quit();

    logger( DEBUG, "Ending");
}