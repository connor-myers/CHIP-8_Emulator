#ifndef GRAPHICS_H
#define GRAPHICS_H

/** Includes **/
#include "SDL2/SDL.h"
#include "settings.h"
#include "exit.h"

/** Constants **/

#define SCREEN_HEIGHT           32              // CHIP-8 is 32 pixels tall
#define SCREEN_WIDTH            64              // CHIP-8 is 64 pixels wide

/** Typedefs **/

/** Functions **/
void init_display(SDL_Window **window, Settings *userSettings);
void update_display(SDL_Window *window, u_int8_t display[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t displayScale);

#endif