#include "headers/chip8.h"

/*
        summary:        Initialises a new CHIP8 struct to have default
                        values

        chip8:          Pointer to new/empty CHIP8 struct                
*/
void init_CHIP8(CHIP8 *chip8, Settings *userSettings)
{
        // setting seed for random number generation
        srand(time(NULL));

        // Ensuring all memory cells, registers, stack and keyboard values are
        // set to 0 initiall;y
        memset(chip8->memory, 0, MEMORY_SIZE * sizeof(uint8_t));
        memset(chip8->registers, 0, NUM_REGISTERS * sizeof(uint8_t));
        memset(chip8->stack, 0, STACK_SIZE * sizeof(uint16_t));
        memset(chip8->keyboard, 0, NUM_KEYS * sizeof(uint8_t));

        // Ensuring special registers are set to 0 initially
        chip8->sp = 0;
        chip8->pc = PROGRAM_START;
        chip8->i = 0;
        chip8->drawFlag = 0;
        chip8->delayTimer = 0;
        chip8->soundTimer = 0;

        // Setting all display bits to 0
        for (int i = 0; i < SCREEN_HEIGHT; i++)
        {
                memset(chip8->display[i], 0, SCREEN_WIDTH * sizeof(uint8_t));
        } 
        memset(chip8->display, 0, SCREEN_HEIGHT * sizeof(uint8_t));

        // Loading the font data into memory
        load_font_data(chip8);

        // Loading user settings into main module
        chip8->userSettings = userSettings;
}
/*
    summary:    Loads the font data into memory

    chip8:      Pointer to CHIP8 struct
*/
void load_font_data(CHIP8 *chip8)
{
    // 0
    chip8->memory[0x000] = 0xF0;
    chip8->memory[0x001] = 0x90;
    chip8->memory[0x002] = 0x90;
    chip8->memory[0x003] = 0x90;
    chip8->memory[0x004] = 0xF0;

    // 1
    chip8->memory[0x005] = 0x20;
    chip8->memory[0x006] = 0x60;
    chip8->memory[0x007] = 0x20;
    chip8->memory[0x008] = 0x20;
    chip8->memory[0x009] = 0x70;

    // 2
    chip8->memory[0x00A] = 0xF0;
    chip8->memory[0x00B] = 0x10;
    chip8->memory[0x00C] = 0xF0;
    chip8->memory[0x00D] = 0x80;
    chip8->memory[0x00E] = 0xF0;

    // 3
    chip8->memory[0x00F] = 0xF0;
    chip8->memory[0x010] = 0x10;
    chip8->memory[0x011] = 0xF0;
    chip8->memory[0x012] = 0x10;
    chip8->memory[0x013] = 0xF0;

    // 4
    chip8->memory[0x014] = 0x90;
    chip8->memory[0x015] = 0x90;
    chip8->memory[0x016] = 0xF0;
    chip8->memory[0x017] = 0x10;
    chip8->memory[0x018] = 0x10;

    // 5
    chip8->memory[0x019] = 0xF0;
    chip8->memory[0x01A] = 0x80;
    chip8->memory[0x01B] = 0xF0;
    chip8->memory[0x01C] = 0x10;
    chip8->memory[0x01D] = 0xF0;

    // 6
    chip8->memory[0x01E] = 0xF0;
    chip8->memory[0x01F] = 0x80;
    chip8->memory[0x020] = 0xF0;
    chip8->memory[0x021] = 0x90;
    chip8->memory[0x022] = 0xF0;

    // 7
    chip8->memory[0x023] = 0xF0;
    chip8->memory[0x024] = 0x10;
    chip8->memory[0x025] = 0x20;
    chip8->memory[0x026] = 0x40;
    chip8->memory[0x027] = 0x40;

    // 8
    chip8->memory[0x028] = 0xF0;
    chip8->memory[0x029] = 0x90;
    chip8->memory[0x02A] = 0xF0;
    chip8->memory[0x02B] = 0x90;
    chip8->memory[0x02C] = 0xF0;

    // 9
    chip8->memory[0x02D] = 0xF0;
    chip8->memory[0x02E] = 0x90;
    chip8->memory[0x02F] = 0xF0;
    chip8->memory[0x030] = 0x10;
    chip8->memory[0x031] = 0xF0;

    // A
    chip8->memory[0x032] = 0xF0;
    chip8->memory[0x033] = 0x90;
    chip8->memory[0x034] = 0xF0;
    chip8->memory[0x035] = 0x90;
    chip8->memory[0x036] = 0x90;

    // B
    chip8->memory[0x037] = 0xE0;
    chip8->memory[0x038] = 0x90;
    chip8->memory[0x039] = 0xE0;
    chip8->memory[0x03A] = 0x90;
    chip8->memory[0x03B] = 0xE0;

    // C
    chip8->memory[0x03C] = 0xF0;
    chip8->memory[0x03D] = 0x80;
    chip8->memory[0x03E] = 0x80;
    chip8->memory[0x03F] = 0x80;
    chip8->memory[0x040] = 0xF0;

    // D
    chip8->memory[0x041] = 0xE0;
    chip8->memory[0x042] = 0x90;
    chip8->memory[0x043] = 0x90;
    chip8->memory[0x044] = 0x90;
    chip8->memory[0x045] = 0xE0;

    // E
    chip8->memory[0x046] = 0xF0;
    chip8->memory[0x047] = 0x80;
    chip8->memory[0x048] = 0xF0;
    chip8->memory[0x049] = 0x80;
    chip8->memory[0x04A] = 0xF0;

    // F
    chip8->memory[0x04B] = 0xF0;
    chip8->memory[0x04C] = 0x80;
    chip8->memory[0x04D] = 0xF0;
    chip8->memory[0x04E] = 0x80;
    chip8->memory[0x04F] = 0x80;
}

