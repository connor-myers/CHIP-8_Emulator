#include "headers/chip8.h"

/*
        summary:        Initialises a new CHIP8 struct to have default
                        values

        chip8:          Pointer to new/empty CHIP8 struct                
*/
void init_CHIP8(CHIP8 *chip8, Settings *userSettings)
{
        // setting seed for random number generation (required by Cxkk opcode)
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
        summary:        Loads ROM into CHIP8 memory
        
        chip8:          Pointer to CHIP8 struct

        rom:            Path to ROM file

*/
void load_rom(CHIP8 *chip8, char *rom)
{
        //  Opening ROM 
        FILE *file = fopen(rom, "r");
        if (file == NULL)
        {
                exit_with_msg(BAD_ROM);
        }

        // Putting ROM into memory
        int n = 0;
        int c;
        while (c = fgetc(file), c != EOF)
        {
        chip8->memory[0x200 + n] = (char) c;
        n++;
        }        
}

/*
        summary:        Updates the timers 

        chip8:          Pointer to CHIP8 struct
*/
void update_timers(CHIP8 *chip8)
{
        time_t currentTime = GET_TIME_IN_MS;
        if (currentTime - chip8->lastTimerUpdate > TIMER_PERIOD)
        {
                if (chip8->delayTimer > 0)
                {
                chip8->delayTimer--;
                }
                if (chip8->soundTimer > 0)
                {
                        chip8->soundTimer--;
                }
                currentTime = currentTime; 
        }
}

/*
        summary:        Runs a single cycle of the emulated CHIP-8 chip8

        chip8:          Pointer to CHIP8 struct
*/
void run_cpu_cycle(CHIP8 *chip8)
{
        Opcode instruction;
        get_next_instruction(chip8, &instruction);
        execute_instruction(chip8, instruction);
}

/*
        summary:        Gets the next instruction and puts it inside
                        pointer to opcode provided.

        chip8:          Pointer to CHIP8 struct

        instruction:    Pointer to Opcode; where instruction will be put

*/
void get_next_instruction(CHIP8 *chip8, Opcode *instruction)
{
        *instruction = chip8->memory[chip8->pc] << 8
                        | chip8->memory[chip8->pc + 1];    
        // each instruction takes 2 cells of memory, hence + 2                
        chip8->pc += 2; 
}

/*
        summary:        Parses opcode and executes that instruction

        chip8:          Pointer to CHIP8 struct

        instruction:    The instruction to be executed

*/
void execute_instruction(CHIP8 *chip8, Opcode instruction)
{
        switch (instruction & 0xF000) 
        {
                case 0x0000:
                switch (instruction)
                {
                        case 0x00E0:
                        {
                                // Clear the display
                                for (int i = 0; i < SCREEN_HEIGHT; i++)
                                {
                                        memset(chip8->display[i], 0, SCREEN_WIDTH * sizeof(uint8_t));
                                } 
                                memset(chip8->display, 0, SCREEN_HEIGHT * sizeof(uint8_t));
                        }
                        break;

                        case 0x00EE:
                        {
                                // Return from subroutine
                                chip8->sp--;
                                chip8->pc = chip8->stack[chip8->sp];
                        }
                        break;    
                }
                break;

                case 0x1000:
                {
                        // Jump to location nnn.
                        chip8->pc = instruction & 0x0FFF;
                }
                break;

                case 0x2000:
                {
                        // Call subroutine at nnn.
                        chip8->stack[chip8->sp] = chip8->pc;
                        chip8->sp++;
                        chip8->pc = instruction & 0x0FFF;
                }
                break;  

                case 0x3000:
                {
                        // Skip next instruction if Vx == NN (0x3XNN)
                        uint8_t x = chip8->registers
                                        [NTH_HEX_DIGIT(instruction, 2)];
                        uint8_t kk = instruction & 0x00FF;
                if (x == kk)
                {
                        chip8->pc += 2;
                }
                }
                break;

                case 0x4000:
                {
                        // Skip next instruction if Vx != NN (0x3XNN)
                        uint8_t x = chip8->registers
                                        [NTH_HEX_DIGIT(instruction, 2)];
                        uint8_t kk = instruction & 0x00FF;
                        if (x != kk)
                        {
                                chip8->pc += 2;
                        }
                }
                break;

                case 0x5000:
                {
                        // SKip next instruction if Vx == Vy (0x5XY0)
                        uint8_t x = chip8->registers
                                        [NTH_HEX_DIGIT(instruction, 2)];
                        uint8_t y = chip8->registers
                                        [NTH_HEX_DIGIT(instruction, 1)];
                        if (x == y)
                        {
                                chip8->pc += 2;
                        }
                }
                break;
                
                case 0x6000:
                {
                        // Sets Vx to NN (0x6XNN)
                        uint8_t kk = instruction & 0x00FF;
                        uint8_t x = NTH_HEX_DIGIT(instruction, 2);
                        chip8->registers[x] = kk;               
                }
                break;
                
                case 0x7000:
                {
                        uint8_t kk = instruction & 0x00FF;
                        uint8_t x = NTH_HEX_DIGIT(instruction, 2);
                        chip8->registers[x] += kk;
                }
                break;

                case 0x8000:
                {
                        uint8_t x = NTH_HEX_DIGIT(instruction, 2);
                        uint8_t y = NTH_HEX_DIGIT(instruction, 1);
                        switch (instruction & 0x000F)
                        {
                                case 0x0:
                                {
                                        chip8->registers[x] = chip8->registers[y];
                                }
                                break;

                                case 0x1:
                                {
                                        chip8->registers[x] = chip8->registers[x] | chip8->registers[y];
                                }
                                break;

                                case 0x2:
                                {
                                        chip8->registers[x] = chip8->registers[x] & chip8->registers[y];
                                }
                                break;

                                case 0x3:
                                {
                                        chip8->registers[x] = chip8->registers[x] ^ chip8->registers[y];
                                }
                                break; 

                                case 0x4:
                                {
                                        // so we can store 8 bit overflow
                                        unsigned short result = chip8->registers[x] + chip8->registers[y]; 
                                        if (result > 255)
                                        {
                                                chip8->registers[0xF] = 1;
                                        } else {
                                                chip8->registers[0xF] = 0;
                                        }
                                        chip8->registers[x] = result & 0xFF;
                                }
                                break;

                                case 0x5:
                                {
                                        if(chip8->registers[x] > chip8->registers[y])
                                        {
                                                chip8->registers[0xF] = 1;
                                        } else {
                                                chip8->registers[0xF] = 0;
                                        }
                                        chip8->registers[x] -= chip8->registers[y];
                                }
                                break;

                                case 0x6:
                                {
                                        chip8->registers[0xF] = chip8->registers[x] & 1 == 1 ? 1 : 0;
                                        chip8->registers[x] /= 2;
                                }
                                break;

                                case 0x7:
                                {
                                        chip8->registers[0xF] = chip8->registers[y] > chip8->registers[x] ? 1 : 0;
                                        chip8->registers[x] = chip8->registers[y] - chip8->registers[x];
                                }
                                break;  
                                
                                case 0xE:
                                {
                                        chip8->registers[0xF] = chip8->registers[x] >> 7 == 1 ? 1 : 0;
                                        chip8->registers[x] *= 2;
                                }
                                break;            
                        }
                }
                break; 

                case 0x9000:
                {
                        uint8_t x = NTH_HEX_DIGIT(instruction, 2);
                        uint8_t y = NTH_HEX_DIGIT(instruction, 1);
                        if (chip8->registers[x] != chip8->registers[y]) {
                                chip8->pc += 2;
                        }            
                }
                break; 

                case 0xA000:
                {
                        chip8->i = instruction & 0x0FFF;       
                }
                break; 

                case 0xB000:
                {
                        chip8->pc = (instruction & 0x0FFF) + chip8->registers[0x0];
                }
                break; 

                case 0xC000:
                {
                        uint8_t random = rand() % 256;
                        chip8->registers[NTH_HEX_DIGIT(instruction, 2)] = random & (instruction & 0x00FF);
                }
                break; 

                case 0xD000:
                {
                        uint8_t n = instruction & 0x000F;
                        uint8_t x = chip8->registers[NTH_HEX_DIGIT(instruction, 2)];
                        uint8_t y = chip8->registers[NTH_HEX_DIGIT(instruction, 1)];
                        chip8->registers[0xF] = 0;
                        for (int i = 0; i < n; i++)
                        {
                                uint8_t sprite = chip8->memory[chip8->i + i];
                                for (int j = 0; j < 8; j++)
                                {
                                if ((sprite >> j & 1) == 1 && chip8->display[(y + i) % SCREEN_HEIGHT][(x + -j + 7) % SCREEN_WIDTH] == 1) 
                                {
                                        chip8->registers[0xF] = 1;
                                }    
                                chip8->display[(y + i) % SCREEN_HEIGHT][(x + ((-1 * j) + 7)) % SCREEN_WIDTH] ^= (sprite >> j) & 1;  
                                }
                        }
                        chip8->drawFlag = 1;
                }
                break; 

                case 0xE000:
                        switch (instruction & 0x00FF)
                        {
                                case 0x009E:
                                {
                                        if (chip8->keyboard[chip8->registers[NTH_HEX_DIGIT(instruction, 2)]])
                                        {
                                                chip8->pc += 2;
                                        }
                                }
                                break;

                                case 0x00A1:
                                {
                                        if (chip8->keyboard[chip8->registers[NTH_HEX_DIGIT(instruction, 2)]] == 0)
                                        {
                                                chip8->pc += 2;
                                        }
                                }
                                break;
                        }
                break;

                case 0xF000:
                {
                        uint8_t x = NTH_HEX_DIGIT(instruction, 2);
                        switch (instruction & 0x00FF)
                        {
                                case 0x07:
                                {
                                        chip8->registers[x] = chip8->delayTimer;
                                }
                                break;

                                case 0x0A:
                                {
                                        if (chip8->keyboard[0])
                                        {
                                                chip8->registers[x] = 0;
                                        }
                                        else if (chip8->keyboard[1])
                                        {
                                                chip8->registers[x] = 1;
                                        }
                                        else if (chip8->keyboard[2])
                                        {
                                                chip8->registers[x] = 2;
                                        }
                                        else if (chip8->keyboard[3])
                                        {
                                                chip8->registers[x] = 3;
                                        }
                                        else if (chip8->keyboard[4])
                                        {
                                                chip8->registers[x] = 4;
                                        }
                                        else if (chip8->keyboard[5])
                                        {
                                                chip8->registers[x] = 5;
                                        }
                                        else if (chip8->keyboard[6])
                                        {
                                                chip8->registers[x] = 6;
                                        }
                                        else if (chip8->keyboard[7])
                                        {
                                                chip8->registers[x] = 7;
                                        }
                                        else if (chip8->keyboard[8])
                                        {
                                                chip8->registers[x] = 8;
                                        }
                                        else if (chip8->keyboard[9])
                                        {
                                                chip8->registers[x] = 9;
                                        }
                                        else if (chip8->keyboard[0xA])
                                        {
                                                chip8->registers[x] = 0xA;
                                        }
                                        else if (chip8->keyboard[0xB])
                                        {
                                                chip8->registers[x] = 0xB;
                                        }
                                        else if (chip8->keyboard[0xC])
                                        {
                                                chip8->registers[x] = 0xC;
                                        }
                                        else if (chip8->keyboard[0xD])
                                        {
                                                chip8->registers[x] = 0xD;
                                        }
                                        else if (chip8->keyboard[0xE])
                                        {
                                                chip8->registers[x] = 0xE;
                                        }
                                        else if (chip8->keyboard[0xF])
                                        {
                                                chip8->registers[x] = 0xF;
                                        }
                                        else
                                        {
                                                chip8->pc -= 2;
                                        }                 
                                }
                                break; 

                                case 0x15:
                                {
                                        chip8->delayTimer = chip8->registers[x];
                                }
                                break; 

                                case 0x18:
                                {
                                        chip8->soundTimer = chip8->registers[x];                                        
                                }
                                break;

                                case 0x1E:
                                {
                                        chip8->i += chip8->registers[x];                    
                                }
                                break; 

                                case 0x29:
                                {
                                        // font data starts at 0x0000
                                        // And each font data is 5 bytes long
                                        // And they're in order, so...
                                        chip8->i = chip8->registers[x] * 5;                                                       
                                }
                                break; 

                                case 0x33:
                                {
                                        chip8->memory[chip8->i] = NTH_HEX_DIGIT(chip8->registers[x], 2);       
                                        chip8->memory[chip8->i + 1] = NTH_HEX_DIGIT(chip8->registers[x], 1);    
                                        chip8->memory[chip8->i + 2] = NTH_HEX_DIGIT(chip8->registers[x], 0); 
                                }
                                break;

                                case 0x55:
                                {
                                        for (int i = 0; i <= x; i++)
                                        {
                                                chip8->memory[chip8->i + i] = chip8->registers[i];
                                        }
                                }
                                break; 

                                case 0x65:
                                {
                                        for (int i = 0; i <= x; i++)
                                        {
                                                chip8->registers[i] = chip8->memory[chip8->i + i];
                                        }
                                }
                                break;       
                        }
                }
                break;    

                default:
                {
                        exit_with_msg(BAD_INSTRUCTION);
                }
                break;    
        }
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