#include "main.h"
#include "log.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef union {
    uint32_t pixel;
    struct {
        uint8_t red, green, blue, alpha;
    } colors;
} color_t;

color_t black = {.pixel = 0x000000ff};

typedef struct {
    uint16_t w,h;
    color_t * grid; // 32 bits per pixel -> RGBA
} bitmap_t;

typedef struct {
    int x, y;
} point_t;

bitmap_t * alloc_bitmap(w,h) {
    bitmap_t * retval;
    retval = malloc(sizeof(bitmap_t));
    retval->w=w;
    retval->h=h;
    retval->grid = calloc(sizeof(color_t), w*h);
    return retval;
}

void free_bitmap(bitmap_t *junk) {
    free(junk->grid);
    free(junk);
}

int screenx=320;
int screeny=200;

void renderline(bitmap_t *bitmap, point_t *start, point_t *end, int width, color_t* color) {
    // recall y=mx+b
    float m = ((float) end->y - (float) start->y)/((float) end->x - (float) start->x);
    int b = (int) (((float) start->x * m) - (float) start->y);

    // TODO: handle width of line
    for(int x = start->x; x < end->x; x++) {
        if(x < 0 || x > bitmap->w) { continue; }
        int y = (int) (m*(float)x) + b;
        if( y < 0 || y > bitmap->h ) { continue; }
        memcpy(bitmap->grid + x * y, color, sizeof(color_t));
    }
}

void fill( bitmap_t * bitmap, color_t * color) {
    logger(DEBUG,"Filling ...");
    int pixels = bitmap->w*bitmap->h;
    for( int i = 0; i < pixels; i++) {
        bcopy(color, bitmap->grid+i, sizeof( color_t));
    }
    logger(DEBUG,"Filling ... done!");
}

// naively assume that bitmaps are the same size
// naively bitwise-and the colors together for a weird effect
void naive_overlay( bitmap_t *higher, bitmap_t *lower) {
    int pixels = higher->w * higher->h;
    for(int i=0; i < pixels; i++) {
        lower->grid[i].pixel &= higher->grid[i].pixel;
    }
}

void shrink(bitmap_t *output, bitmap_t* input) {

}

void rotate( bitmap_t *output, bitmap_t* input, float deg) {

}

void darken( bitmap_t *bitmap, float howmuch) {
    if( howmuch >= 1) {
        logger(WARN, "Unexpected value to darken; no changes.");
        return;
    } // special case: no darkening
    if( howmuch <= 0) {
        fill(bitmap, &black);
        return;
    } // special case: full darkening

    // convert rgb values to hsv; multiply 'v' by howmuch (0..1); convert back to rgb
    // for each pixel.
}

int main(int argc, char ** argv) {
    logger(DEBUG, "Starting");

    bitmap_t* redbox_bitmap = alloc_bitmap(screenx*2,screeny*2);
    bitmap_t* bluebox_bitmap = alloc_bitmap(screenx*2,screeny*2);
    bitmap_t* greenbox_bitmap = alloc_bitmap(screenx*2,screeny*2);
    bitmap_t* background = alloc_bitmap( screenx*2,screeny*2);
    bitmap_t* display_bitmap = alloc_bitmap(screenx, screeny);

    fill(background, &black);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * win = SDL_CreateWindow("foo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenx,screeny, SDL_WINDOW_SHOWN);
    if( win == NULL) {
        logger(ERROR, SDL_GetError());
    }

    SDL_UpdateWindowSurface(win);
    SDL_Surface * windowSurface = SDL_GetWindowSurface(win);

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