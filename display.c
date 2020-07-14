#include "display.h"

void init_display()
{
    SDL_Window *window;
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "CHIP-8 Emulator",                 // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        SCREEN_WIDTH * SCALE_FACTOR,       // width, in pixels
        SCREEN_HEIGHT * SCALE_FACTOR,      // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    if (window == NULL)
    {
        err_msg(GRAPHICS_INIT_ERROR);
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())

    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;

    return;
}