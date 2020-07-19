#ifndef DISPLAY_H
#define DISPLAY_H

#include "SDL2/SDL.h"
#include "errs.h"

#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64
#define SCALE_FACTOR 25

void init_display(SDL_Window **window);
void update_display(SDL_Window *window, u_int8_t display[SCREEN_HEIGHT][SCREEN_WIDTH]);
void clear_display(uint8_t display[SCREEN_HEIGHT][SCREEN_WIDTH]);

#endif
