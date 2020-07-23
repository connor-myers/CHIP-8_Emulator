#include "headers/graphics.h"

/*
    summary:    Initialises a new SDL display into inputted SDL_Window pointer

    window:     Pointer to empty SDL Window
*/
void init_display(SDL_Window **window, Settings *userSettings)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    *window = SDL_CreateWindow(
        "CHIP-8 Emulator",                              // window title
        SDL_WINDOWPOS_UNDEFINED,                        // initial x position
        SDL_WINDOWPOS_UNDEFINED,                        // initial y position
        SCREEN_WIDTH * userSettings->displayScale,       // width, in pixels
        SCREEN_HEIGHT * userSettings->displayScale,      // height, in pixels
        SDL_WINDOW_OPENGL                               // flags - see below
    );

    if (*window == NULL)
    {
        exit_with_msg(GRAPHICS_INIT_ERROR);
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
void update_display(SDL_Window *window, u_int8_t display[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t displayScale)
{
    SDL_Renderer *renderer = SDL_GetRenderer(window);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // the rect color (solid white)

    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            if (display[i][j] == 1) {
                SDL_Rect rect = {j * displayScale, i * displayScale, displayScale, displayScale};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    SDL_RenderPresent(renderer); // display to screen

    return;
}
