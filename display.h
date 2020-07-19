#ifndef DISPLAY_H
#define DISPLAY_H

#include "SDL2/SDL.h"
#include "errs.h"

#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64
#define SCALE_FACTOR 25

#define DISPLAY_HEIGHT 32
#define DISPLAY_WIDTH 8

void init_display(SDL_Window **window);
void update_display(SDL_Window *window, u_int8_t display[DISPLAY_HEIGHT][DISPLAY_WIDTH]);
void clear_display(uint8_t display[DISPLAY_HEIGHT][DISPLAY_WIDTH]);

#endif
