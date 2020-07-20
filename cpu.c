#include "cpu.h"

/*
    summary:    Initialises a new CPU

    cpu:        Pointer to an empty CPU struct
*/
void cpu_init(CPU *cpu)
{
    srand(time(NULL)); // setting seed for random number generation
    memset(cpu->memory, 0, MEMORY_SIZE * sizeof(uint8_t));
    memset(cpu->registers, 0, NUM_REGISTERS * sizeof(uint8_t));
    memset(cpu->keyboard, 0, NUM_KEYS * sizeof(uint8_t));
    load_font_data(cpu);
    memset(cpu->stack, 0, STACK_SIZE * sizeof(uint16_t));
    cpu->sp = 0;
    cpu->pc = PROGRAM_START;
    cpu->i = 0;
    cpu->drawFlag = 0;
    cpu->lastCycleTime = clock() / (CLOCKS_PER_SEC / 1000);
    cpu->delayTimer = 0;
    cpu->soundTimer = 0;
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        memset(cpu->display[i], 0, SCREEN_WIDTH * sizeof(uint8_t));
    } 
    memset(cpu->display, 0, SCREEN_HEIGHT * sizeof(uint8_t));
}

/*
    summary:    Emulates a single CPU clock cycle

    cpu:        Pointer to CPU
*/
void process_cycle(CPU *cpu)
{
    Opcode instruction = get_next_instruction(cpu);
    perform_instruction(cpu, instruction);
}

/*
    summary:    Gets the next instruction

    cpu:        Pointer to CPU
*/
Opcode get_next_instruction(CPU *cpu)
{
    Opcode instruction = cpu->memory[cpu->pc] << 8 | cpu->memory[cpu->pc + 1];    
    cpu->pc += 2;           // each instruction takes 2 cells of memory, hence +2
    fflush(stdout);
    return instruction;
}

/*
    summary:    Loads ROM into memory

    cpu:        Pointer to CPU

    file:       The file to load data from
*/
void load_rom(CPU *cpu, FILE *file)
{
    int n = 0;
    int c;
    while (c = fgetc(file), c != EOF)
    {
        cpu->memory[0x200 + n] = (char) c;
        n++;
    }
}

/*
    summary:    Updates the values of the two CHIP-8 timers

    cpu:        Pointer to CPU
*/
void update_timers(CPU *cpu)
{
    time_t currentTime = clock() / (CLOCKS_PER_SEC / 1000);

    // while (currentTime - cpu->lastCycleTime > PERIOD) {
    //     if (cpu->delayTimer > 0)
    //     {
    //         cpu->delayTimer--;
    //     }
    //     if (cpu->soundTimer > 0)
    //     {
    //         cpu->soundTimer--;
    //     }
    //     cpu->lastCycleTime = currentTime;
    // }
    if (cpu->delayTimer > 0)
    {
        cpu->delayTimer--;
    }
    if (cpu->soundTimer > 0)
    {
        cpu->soundTimer--;
    }
}

void perform_instruction(CPU *cpu, Opcode instruction)
{
    switch (instruction & 0xF000) 
    {
        case 0x0000:
            switch (instruction)
            {
                case 0x00E0:
                {
                    // Clear the display
                    clear_display(cpu->display);
                }
                break;

                case 0x00EE:
                {
                    // Return from subroutine
                    cpu->sp--;
                    cpu->pc = cpu->stack[cpu->sp];
                }
                break;    
            }
            break;

        case 0x1000:
        {
            // Jump to location nnn.
            cpu->pc = instruction & 0x0FFF;
        }
        break;

        case 0x2000:
        {
            // Call subroutine at nnn.
            cpu->stack[cpu->sp] = cpu->pc;
            cpu->sp++;
            cpu->pc = instruction & 0x0FFF;
        }
        break;  

        case 0x3000:
        {
            // Skip next instruction if Vx == NN (0x3XNN)
            uint8_t x = cpu->registers[get_nth_hex_digit(instruction, 2)];
            uint8_t kk = instruction & 0x00FF;
            if (x == kk)
            {
                cpu->pc += 2;
            }
        }
        break;

        case 0x4000:
        {
            // Skip next instruction if Vx != NN (0x3XNN)
            uint8_t x = cpu->registers[get_nth_hex_digit(instruction, 2)];
            uint8_t kk = instruction & 0x00FF;
            if (x != kk)
            {
                cpu->pc += 2;
            }
        }
        break;

        case 0x5000:
        {
            // SKip next instruction if Vx == Vy (0x5XY0)
            uint8_t x = cpu->registers[get_nth_hex_digit(instruction, 2)];
            uint8_t y = cpu->registers[get_nth_hex_digit(instruction, 1)];
            if (x == y) {
                cpu->pc += 2;
            }
        }
        break;
            
        case 0x6000:
        {
            // Sets Vx to NN (0x6XNN)
            uint8_t kk = instruction & 0x00FF;
            uint8_t x = get_nth_hex_digit(instruction, 2);
            cpu->registers[x] = kk;               
        }
        break;
            
        case 0x7000:
        {
            uint8_t kk = instruction & 0x00FF;
            uint8_t x = get_nth_hex_digit(instruction, 2);
            cpu->registers[x] += kk;
        }
        break;

        case 0x8000:
        {
            uint8_t x = get_nth_hex_digit(instruction, 2);
            uint8_t y = get_nth_hex_digit(instruction, 1);
            switch (instruction & 0x000F)
            {
                case 0x0:
                {
                    cpu->registers[x] = cpu->registers[y];
                }
                break;
                case 0x1:
                {
                    cpu->registers[x] = cpu->registers[x] | cpu->registers[y];
                }
                break;
                case 0x2:
                {
                    cpu->registers[x] = cpu->registers[x] & cpu->registers[y];
                }
                break;
                case 0x3:
                {
                    cpu->registers[x] = cpu->registers[x] ^ cpu->registers[y];
                }
                break; 
                case 0x4:
                {
                    // so we can store 8 bit overflow
                    unsigned short result = cpu->registers[x] + cpu->registers[y]; 
                    if (result > 255)
                    {
                        cpu->registers[0xF] = 1;
                    } else {
                        cpu->registers[0xF] = 0;
                    }
                    cpu->registers[x] = result & 0xFF;
                    break;
                }
                case 0x5:
                {
                    if(cpu->registers[x] > cpu->registers[y])
                    {
                        cpu->registers[0xF] = 1;
                    } else {
                        cpu->registers[0xF] = 0;
                    }
                    cpu->registers[x] -= cpu->registers[y];
                }
                break;
                case 0x6:
                {
                    cpu->registers[0xF] = cpu->registers[x] & 1 == 1 ? 1 : 0;
                    cpu->registers[x] /= 2;
                }
                break;
                case 0x7:
                {
                    cpu->registers[0xF] = cpu->registers[y] > cpu->registers[x] ? 1 : 0;
                    cpu->registers[x] = cpu->registers[y] - cpu->registers[x];
                }
                    break;  
                case 0xE:
                {
                    cpu->registers[0xF] = cpu->registers[x] >> 7 == 1 ? 1 : 0;
                    cpu->registers[x] *= 2;
                }
                    break;            
            }
            break; 
        }

        case 0x9000:
        {
            uint8_t x = get_nth_hex_digit(instruction, 2);
            uint8_t y = get_nth_hex_digit(instruction, 1);
            if (cpu->registers[x] != cpu->registers[y]) {
                cpu->pc += 2;
            }            
        }
        break; 

        case 0xA000:
        {
            cpu->i = instruction & 0x0FFF;       
        }
        break; 

        case 0xB000:
        {
            cpu->pc = (instruction & 0x0FFF) + cpu->registers[0x0];
        }
        break; 

        case 0xC000:
        {
            uint8_t random = rand() % 256;
            cpu->registers[get_nth_hex_digit(instruction, 2)] = random & (instruction & 0x00FF);
        }
        break; 

        // this probably doesn't work
        case 0xD000:
        {
            uint8_t n = instruction & 0x000F;
            uint8_t x = cpu->registers[get_nth_hex_digit(instruction, 2)];
            uint8_t y = cpu->registers[get_nth_hex_digit(instruction, 1)];
            cpu->registers[0xF] = NO_COLLISION;
            for (int i = 0; i < n; i++)
            {
                uint8_t sprite = cpu->memory[cpu->i + i];
                for (int j = 0; j < 8; j++)
                {
                    // if both are one, than they're going to cancel out in XOR; thus a collision
                    if (cpu->display[(y + i) % SCREEN_HEIGHT][(x + j) % SCREEN_WIDTH] == 1 && (sprite >> j) & 1 == 1)
                    {
                        cpu->registers[0xF] = COLLISION;
                    }
                    cpu->display[(y + i) % SCREEN_HEIGHT][(x + -j + 8) % SCREEN_WIDTH] ^= (sprite >> j) & 1;            
                }
            }
            cpu->drawFlag = 1;
        }
        break; 

        case 0xE000:
            switch (instruction & 0x00FF)
            {
                case 0x009E:
                {
                    if (cpu->keyboard[cpu->registers[get_nth_hex_digit(instruction, 2)]])
                    {
                        cpu->pc += 2;
                    }
                }
                break;

                case 0x00A1:
                {
                    if (cpu->keyboard[cpu->registers[get_nth_hex_digit(instruction, 2)]] == 0)
                    {
                        cpu->pc += 2;
                    }
                }
                break;
                        
            }
            break;

        case 0xF000:
        {
            uint8_t x = get_nth_hex_digit(instruction, 2);
            switch (instruction & 0x00FF)
            {
                case 0x07:
                {
                    cpu->registers[x] = cpu->delayTimer;
                }
                break;

                case 0x0A:
                {
                    // while(1)
                    // {
                    //     uint8_t quit = false;
                    //     const uint8_t *state = SDL_GetKeyboardState(NULL);
                    //     if (state[SDLK_1])
                    //     {
                    //         cpu->keyboard[0x0] = 1;
                    //         quit = true;
                    //     } else if (state[SDLK_2]) {
                    //         cpu->keyboard[0x1] = 1;
                    //         quit = true;
                    //     } else if (state[SDLK_3]) {
                    //         cpu->keyboard[0x2] = 1;
                    //         quit = true;
                    //     } else if (state[SDLK_4]) {
                    //         cpu->keyboard[0x3] = 1;
                    //         quit = true;
                    //     } else if (state[SDLK_q]) {
                    //         cpu->keyboard[0x4] = 1;
                    //         quit = true;
                    //     } else if (state[SDLK_w]) {
                    //         cpu->keyboard[0x5] = 1;
                    //         quit = true;
                    //     } else if (state[SDLK_e]) {
                    //         cpu->keyboard[0x6] = 1;
                    //         quit = true;
                    //     } else if (state[SDLK_r]) {
                    //         cpu->keyboard[0x7] = 1;
                    //         quit = true;
                    //     } else if (state[SDLK_a]) {
                    //         cpu->keyboard[0x8] = 1;
                    //         quit = true;
                    //     } else if (state[SDLK_s]) {
                    //         cpu->keyboard[0x9] = 1;
                    //         quit = true;
                    //     } else if (state[SDLK_d]) {
                    //         cpu->keyboard[0xA] = 1;
                    //         quit = true;
                    //     } else if (state[SDLK_f]) {
                    //         cpu->keyboard[0xB] = 1;
                    //         quit = true;
                    //     } else if (state[SDLK_z]) {
                    //         cpu->keyboard[0xC] = 1;
                    //         quit = true;
                    //     } else if (state[SDLK_x]) {
                    //         cpu->keyboard[0xD] = 1;
                    //         quit = true;
                    //     } else if (state[SDLK_c]) {
                    //         cpu->keyboard[0xE] = 1;
                    //         quit = true;
                    //     } else if (state[SDLK_v]) {
                    //         cpu->keyboard[0xF] = 1;
                    //         quit = true;
                    //     } else {
                    //         // key not part of chip-8
                    //     }
                    //     if (quit)
                    //     {
                    //         break;
                    //     }

                    // }
                }
                break; 

                case 0x15:
                {
                    cpu->delayTimer = cpu->registers[x];
                }
                break; 

                case 0x18:
                {
                    cpu->soundTimer = cpu->registers[x];                                        
                }
                break;

                case 0x1E:
                {
                    cpu->i += cpu->registers[x];                    
                }
                break; 

                case 0x29:
                {
                    cpu->i = get_font_address(cpu->registers[x]);                                                         
                }
                break; 

                case 0x33:
                {
                    cpu->memory[cpu->i] = get_nth_dec_digit(cpu->registers[x], 2);       
                    cpu->memory[cpu->i + 1] = get_nth_dec_digit(cpu->registers[x], 1);    
                    cpu->memory[cpu->i + 2] = get_nth_dec_digit(cpu->registers[x], 0); 
                                       
                }
                break;

                case 0x55:
                {
                    for (int i = 0; i <= x; i++)
                    {
                        cpu->memory[cpu->i + i] = cpu->registers[i];
                    }
                }
                break; 

                case 0x65:
                {
                    for (int i = 0; i <= x; i++)
                    {
                        cpu->registers[i] = cpu->memory[cpu->i + i];
                    }
                }
                break;       
            }
        }
        break;    

        default:
            err_msg(BAD_INSTRUCTION);
            break;    
    }    
}

/*
    summary:    Gets the nth hex digit from a number

    number:      The number to get the nth place from
    
    n:           The digits place to get the nth hex digit from
*/
uint8_t get_nth_hex_digit(uint16_t number, uint8_t n)
{
    while (n--) {
        number /= 0x10;
    }
    return (number % 0x10);
}

/*
    summary:    Gets the nth dec digit from a number

    number:      The number to get the nth place from
    
    n:           The digits place to get the nth dec digit from
*/
uint8_t get_nth_dec_digit(uint16_t number, uint8_t n)
{
    while (n--) {
        number /= 10;
    }
    return (number % 10);
}

/*
    summary:    Gets the location in memory for font for the corresponding hex digit

    value:      The hex digit to get location in memory for the font for
*/
uint8_t get_font_address(uint8_t value)
{
    return value * 5;
}

/*
    summary:    Loads the font data into memory

    cpu:        Pointer to CPU
*/
void load_font_data(CPU *cpu)
{
    // 0
    cpu->memory[0x000] = 0xF0;
    cpu->memory[0x001] = 0x90;
    cpu->memory[0x002] = 0x90;
    cpu->memory[0x003] = 0x90;
    cpu->memory[0x004] = 0xF0;

    // 1
    cpu->memory[0x005] = 0x20;
    cpu->memory[0x006] = 0x60;
    cpu->memory[0x007] = 0x20;
    cpu->memory[0x008] = 0x20;
    cpu->memory[0x009] = 0x70;

    // 2
    cpu->memory[0x00A] = 0xF0;
    cpu->memory[0x00B] = 0x10;
    cpu->memory[0x00C] = 0xF0;
    cpu->memory[0x00D] = 0x80;
    cpu->memory[0x00E] = 0xF0;

    // 3
    cpu->memory[0x00F] = 0xF0;
    cpu->memory[0x010] = 0x10;
    cpu->memory[0x011] = 0xF0;
    cpu->memory[0x012] = 0x10;
    cpu->memory[0x013] = 0xF0;

    // 4
    cpu->memory[0x014] = 0x90;
    cpu->memory[0x015] = 0x90;
    cpu->memory[0x016] = 0xF0;
    cpu->memory[0x017] = 0x10;
    cpu->memory[0x018] = 0x10;

    // 5
    cpu->memory[0x019] = 0xF0;
    cpu->memory[0x01A] = 0x80;
    cpu->memory[0x01B] = 0xF0;
    cpu->memory[0x01C] = 0x10;
    cpu->memory[0x01D] = 0xF0;

    // 6
    cpu->memory[0x01E] = 0xF0;
    cpu->memory[0x01F] = 0x80;
    cpu->memory[0x020] = 0xF0;
    cpu->memory[0x021] = 0x90;
    cpu->memory[0x022] = 0xF0;

    // 7
    cpu->memory[0x023] = 0xF0;
    cpu->memory[0x024] = 0x10;
    cpu->memory[0x025] = 0x20;
    cpu->memory[0x026] = 0x40;
    cpu->memory[0x027] = 0x40;

    // 8
    cpu->memory[0x028] = 0xF0;
    cpu->memory[0x029] = 0x90;
    cpu->memory[0x02A] = 0xF0;
    cpu->memory[0x02B] = 0x90;
    cpu->memory[0x02C] = 0x90;

    // 9
    cpu->memory[0x02D] = 0xF0;
    cpu->memory[0x02E] = 0x90;
    cpu->memory[0x02F] = 0xF0;
    cpu->memory[0x030] = 0x10;
    cpu->memory[0x031] = 0xF0;

    // A
    cpu->memory[0x032] = 0xF0;
    cpu->memory[0x033] = 0x90;
    cpu->memory[0x034] = 0xF0;
    cpu->memory[0x035] = 0x90;
    cpu->memory[0x036] = 0x90;

    // B
    cpu->memory[0x037] = 0xE0;
    cpu->memory[0x038] = 0x90;
    cpu->memory[0x039] = 0xE0;
    cpu->memory[0x03A] = 0x90;
    cpu->memory[0x03B] = 0xE0;

    // C
    cpu->memory[0x03C] = 0xF0;
    cpu->memory[0x03D] = 0x80;
    cpu->memory[0x03E] = 0x80;
    cpu->memory[0x03F] = 0x80;
    cpu->memory[0x040] = 0xF0;

    // D
    cpu->memory[0x041] = 0xE0;
    cpu->memory[0x042] = 0x90;
    cpu->memory[0x043] = 0x90;
    cpu->memory[0x044] = 0x90;
    cpu->memory[0x045] = 0xE0;

    // E
    cpu->memory[0x046] = 0xF0;
    cpu->memory[0x047] = 0x80;
    cpu->memory[0x048] = 0xF0;
    cpu->memory[0x049] = 0x80;
    cpu->memory[0x04A] = 0xF0;

    // F
    cpu->memory[0x04B] = 0xF0;
    cpu->memory[0x04C] = 0x80;
    cpu->memory[0x04D] = 0xF0;
    cpu->memory[0x04E] = 0x80;
    cpu->memory[0x04F] = 0x80;
}
