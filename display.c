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

    Note:       We have a triple nested for-loop because I'm storing the information of 64 pixels in 8 bytes
                Which means we need to bitshift out each bit value. More complicated, but it's more efficient
                to do this. (C does not have a datatype that is 1 bit long, so this is the best we can do)
*/
void update_display(SDL_Window *window, u_int8_t display[SCREEN_HEIGHT][SCREEN_WIDTH])
{
    SDL_Renderer *renderer = SDL_GetRenderer(window);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // the rect color (solid white)

    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            if (display[i][j] == 1) {
                SDL_Rect rect = {j * SCALE_FACTOR, i * SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    SDL_RenderPresent(renderer); // display to screen

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

/*
    summary:    Clears the display

    cpu:        The main CPU Struct
*/
void clear_display(uint8_t display[SCREEN_HEIGHT][SCREEN_WIDTH])
{
    memset(display, 0, SCREEN_HEIGHT);
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        memset(display[i], 0, SCREEN_WIDTH);
    }
}