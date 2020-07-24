#include "headers/input.h"

void process_input(CHIP8 *chip8)
{
                SDL_Event event;
        while (SDL_PollEvent(&event))
        {
                switch (event.type)
                {
                        case SDL_QUIT:
                        {
                                clean_and_exit();
                        } break;

                        case SDL_KEYDOWN:
                        {
                                switch (event.key.keysym.sym)
                                {
                                        case SDLK_ESCAPE:
                                        {
                                                exit(0); // close the game
                                        } break;

                                        case SDLK_x:
                                        {
                                                chip8->keyboard[0] = 1;
                                        } break;

                                        case SDLK_1:
                                        {
                                                chip8->keyboard[1] = 1;
                                        } break;

                                        case SDLK_2:
                                        {
                                                chip8->keyboard[2] = 1;
                                        } break;

                                        case SDLK_3:
                                        {
                                                chip8->keyboard[3] = 1;
                                        } break;

                                        case SDLK_q:
                                        {
                                                chip8->keyboard[4] = 1;
                                        } break;

                                        case SDLK_w:
                                        {
                                                chip8->keyboard[5] = 1;
                                        } break;

                                        case SDLK_e:
                                        {
                                                chip8->keyboard[6] = 1;
                                        } break;

                                        case SDLK_a:
                                        {
                                                chip8->keyboard[7] = 1;
                                        } break;

                                        case SDLK_s:
                                        {
                                                chip8->keyboard[8] = 1;
                                        } break;

                                        case SDLK_d:
                                        {
                                                chip8->keyboard[9] = 1;
                                        } break;

                                        case SDLK_z:
                                        {
                                                chip8->keyboard[0xA] = 1;
                                        } break;

                                        case SDLK_c:
                                        {
                                                chip8->keyboard[0xB] = 1;
                                        } break;

                                        case SDLK_4:
                                        {
                                                chip8->keyboard[0xC] = 1;
                                        } break;

                                        case SDLK_r:
                                        {
                                                chip8->keyboard[0xD] = 1;
                                        } break;

                                        case SDLK_f:
                                        {
                                                chip8->keyboard[0xE] = 1;
                                        } break;

                                        case SDLK_v:
                                        {
                                                chip8->keyboard[0xF] = 1;
                                        } break;
                                }
                        } break;

                        case SDL_KEYUP:
                        {
                                switch (event.key.keysym.sym)
                                {
                                        case SDLK_x:
                                        {
                                                chip8->keyboard[0] = 0;
                                        } break;

                                        case SDLK_1:
                                        {
                                                chip8->keyboard[1] = 0;
                                        } break;

                                        case SDLK_2:
                                        {
                                                chip8->keyboard[2] = 0;
                                        } break;

                                        case SDLK_3:
                                        {
                                                chip8->keyboard[3] = 0;
                                        } break;

                                        case SDLK_q:
                                        {
                                                chip8->keyboard[4] = 0;
                                        } break;

                                        case SDLK_w:
                                        {
                                                chip8->keyboard[5] = 0;
                                        } break;

                                        case SDLK_e:
                                        {
                                                chip8->keyboard[6] = 0;
                                        } break;

                                        case SDLK_a:
                                        {
                                                chip8->keyboard[7] = 0;
                                        } break;

                                        case SDLK_s:
                                        {
                                                chip8->keyboard[8] = 0;
                                        } break;

                                        case SDLK_d:
                                        {
                                                chip8->keyboard[9] = 0;
                                        } break;

                                        case SDLK_z:
                                        {
                                                chip8->keyboard[0xA] = 0;
                                        } break;

                                        case SDLK_c:
                                        {
                                                chip8->keyboard[0xB] = 0;
                                        } break;

                                        case SDLK_4:
                                        {
                                                chip8->keyboard[0xC] = 0;
                                        } break;

                                        case SDLK_r:
                                        {
                                                chip8->keyboard[0xD] = 0;
                                        } break;

                                        case SDLK_f:
                                        {
                                                chip8->keyboard[0xE] = 0;
                                        } break;

                                        case SDLK_v:
                                        {
                                                chip8->keyboard[0xF] = 0;
                                        } break;
                                }
                        } break;
                }
        }
}