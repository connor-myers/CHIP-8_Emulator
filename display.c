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
void update_display(SDL_Window *window, u_int8_t display[DISPLAY_HEIGHT][DISPLAY_WIDTH])
{
    SDL_Renderer *renderer = SDL_GetRenderer(window);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // the rect color (solid white)

        // testing display
    display[0][0] = 0xFF;
    display[1][0] = 0x80;
    display[2][0] = 0xF0;
    display[3][0] = 0x90;
    display[4][0] = 0xF0;

    display[0][1] = 0xF0;
    display[1][1] = 0x90;
    display[2][1] = 0xF0;
    display[3][1] = 0x10;
    display[4][1] = 0xF0;


    for (int i = 0; i < DISPLAY_HEIGHT; i++)
    {
        for (int j = 0; j < DISPLAY_WIDTH; j++)
        {
            for (int k = 7; k >= 0; k--)
            {
                int val = display[i][j] >> k & 1;
                if (val)
                {
                    SDL_Rect rect = {((j * 8) + 7 - k) * SCALE_FACTOR, i * SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR};
                    SDL_RenderFillRect(renderer, &rect);
                }
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