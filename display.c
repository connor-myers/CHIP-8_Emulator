#include "display.h"

/*
    summary:    Initialises a new SDL display into inputted SDL_Window pointer

    window:     Pointer to empty SDL Window
*/
void init_display(SDL_Window **window)
{
    SDL_Init(SDL_INIT_VIDEO);

    *window = SDL_CreateWindow(
        "CHIP-8 Emulator",                 // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        SCREEN_WIDTH * SCALE_FACTOR,       // width, in pixels
        SCREEN_HEIGHT * SCALE_FACTOR,      // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    if (*window == NULL)
    {
        err_msg(GRAPHICS_INIT_ERROR);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderClear(renderer);

    return;
}

/*
    summary:    Updates what's displaying on the window

    window:     Pointer to main SDL_Window   

*/
void update_display(SDL_Window *window, u_int8_t display[DISPLAY_HEIGHT][DISPLAY_WIDTH])
{
    SDL_Renderer *renderer = SDL_GetRenderer(window);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // the rect color (solid red)
    SDL_Rect rect = {50, 50, 50, 50};
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer); // copy to screen
    return;
}

/*
    summary:    Closes the SDL window 

    window:     Pointer to main SDL_Window
*/
void close_display(SDL_Window *window)
{
    return;
}