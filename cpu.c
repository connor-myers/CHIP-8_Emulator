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
    stack_init(&cpu->stack);
    load_font_data(cpu);
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

    while (currentTime - cpu->lastCycleTime > PERIOD) {
        if (cpu->delayTimer > 0)
        {
            cpu->delayTimer--;
        }
        if (cpu->soundTimer > 0)
        {
            cpu->soundTimer--;
        }
        cpu->lastCycleTime = currentTime;
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
                    clear_display(cpu);
                }
                break;

                case 0x00EE:
                {
                    // Return from subroutine
                    cpu->pc = stack_pop(&cpu->stack);
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
            stack_push(&cpu->stack, cpu->pc);
            cpu->pc = instruction & 0x0FFF;
        }
        break;  

        case 0x3000:
        {
            // Skip next instruction if Vx == NN (0x3XNN)
            uint8_t x = cpu->registers[instruction & 0x0F00];
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
            uint8_t x = cpu->registers[instruction & 0x0F00];
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
            uint8_t x = cpu->registers[instruction & 0x0F00];
            uint8_t y = cpu->registers[instruction & 0x00F0];
            if (x == y) {
                cpu->pc += 2;
            }
        }
        break;
            
        case 0x6000:
        {
            // Sets Vx to NN (0x6XNN)
            uint8_t kk = instruction & 0x00FF;
            uint8_t x = instruction & 0x0F00;
            cpu->registers[x] = kk;               
        }
        break;
            
        case 0x7000:
        {
            uint8_t kk = instruction & 0x00FF;
            uint8_t x = instruction & 0x0F00;
            cpu->registers[x] += kk;
        }
        break;

        case 0x8000:
        {
            uint8_t x = instruction & 0x0F00;
            uint8_t y = instruction & 0x00F0;
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
                    unsigned short result = cpu->registers[x] + cpu->registers[y];
                    if (result > 255)
                    {
                        cpu->registers[0xF] = 1;
                    }
                    cpu->registers[x] = result & 0xFF;
                    break;
                }
                case 0x5:
                {
                    if(x > y)
                    {
                        cpu->registers[0xF] = 1;
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
                    cpu->registers[0xF] = cpu->registers[x] & 0x80 == 1 ? 1 : 0;
                    cpu->registers[x] *= 2;
                }
                    break;            
            }
            break; 
        }

        case 0x9000:
        {
            uint8_t x = instruction & 0x0F00;
            uint8_t y = instruction & 0x00F0;
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
            cpu->registers[instruction & 0x0F00] = random & (instruction & 0x00FF);
        }
        break; 

        // this probably doesn't work
        case 0xD000:
        {
            uint8_t n = instruction & 0x000F;
            uint8_t x = cpu->registers[instruction & 0x0F00];
            uint8_t y = cpu->registers[instruction & 0x00F0];
            cpu->registers[0xF] = NO_COLLISION;
            for (int i = 0; i < n; i++)
            {
                uint8_t sprite = cpu->memory[cpu->i + i];
                // (sprite >> j) & 1;
                for (int j = 0; j < 7; j++)
                {
                    // if both are one, than they're going to cancel out in XOR; thus a collision
                    if (cpu->display[(y + i) % SCREEN_HEIGHT][(x + j) % SCREEN_WIDTH] == 1 && (sprite >> j) & 1 == 1)
                    {
                        cpu->registers[0xF] = COLLISION;
                    }
                    cpu->display[(y + i) % SCREEN_HEIGHT][(x + j) % SCREEN_WIDTH] ^= (sprite >> j) & 1;            
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
                    if (cpu->keyboard[cpu->registers[instruction & 0x0F00]])
                    {
                        cpu->pc += 2;
                    }
                }
                break;

                case 0x00A1:
                {
                    if (cpu->keyboard[cpu->registers[instruction & 0x0F00]] == 0)
                    {
                        cpu->pc += 2;
                    }
                }
                break;
                        
            }
            break;

        case 0xF000:
        {
            uint8_t x = instruction & 0x0F00;
            switch (instruction & 0x00FF)
            {
                case 0x07:
                {
                    cpu->registers[x] = cpu->delayTimer;
                }
                break;

                case 0x0A:
                {
                    // TODO 
                    // ? COME BACK TO LATER
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
                    cpu->memory[cpu->i] = get_font_address(cpu->registers[x] / 100);       
                    cpu->memory[cpu->i + 1] = get_font_address((cpu->registers[x] % 100) / 10);    
                    cpu->memory[cpu->i + 2] = get_font_address((cpu->registers[x] % 10));                                               
                }
                break;

                case 0x55:
                {
                    for (int i = 0; i < x; i++)
                    {
                        cpu->memory[cpu->i + i] = cpu->registers[i];
                    }
                }
                break; 

                case 0x65:
                {
                    for (int i = 0; i < x; i++)
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
    summary:    Gets the location in memory for font for the corresponding hex digit

    value:      The hex digit to get location in memory for the font for
*/
uint8_t get_font_address(uint8_t value)
{
    uint8_t location;
    switch (value)
    {
        case 0x0:
            location = 0x000;
            break;
        case 0x1:
            location = 0x005;
            break;
        case 0x2:
            location = 0x00A;
            break;
        case 0x3:
            location = 0x00F;
            break;
        case 0x4:
            location = 0x014;
            break;
        case 0x5:
            location = 0x019;
            break;
        case 0x6:
            location = 0x01E;
            break;
        case 0x7:
            location = 0x023;
            break;
        case 0x8:
            location = 0x028;
            break;
        case 0x9:
            location = 0x02D;
            break;
        case 0xA:
            location = 0x032;
            break;
        case 0xB:
            location = 0x037;
            break;
        case 0xC:
            location = 0x03C;
            break;
        case 0xD:
            location = 0x041;
            break;
        case 0xE:
            location = 0x046;
            break;
        case 0xF:
            location = 0x04B;
            break;   
        default:
            err_msg(UNKNOWN_FONT_DATA);
            break;                                                      
    }
    return location;
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
