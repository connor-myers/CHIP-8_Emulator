#include "cpu.h"

/*
    summary:    Initialises a new CPU

    cpu:        Pointer to an empty CPU struct
*/
void cpu_init(CPU *cpu)
{
    memset(cpu->memory, 0, MEMORY_SIZE * sizeof(unsigned int));
    memset(cpu->registers, 0, NUM_REGISTERS * sizeof(unsigned int));
    stack_init(&cpu->stack);
    load_font_data(cpu);
    cpu->pc = PROGRAM_START; 
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

void perform_instruction(CPU *cpu, Opcode instruction)
{
    switch (instruction & 0xF000) 
    {
        case 0x0000:
            switch (instruction)
            {
                case 0x00E0:
                    // TODO
                    // clear screen
                    break;
                case 0x00EE:
                    // TODO
                    // return from subroutine
                    break;    
            }
            break;

        case 0x1000:
            // Jumps to address NNN.
            cpu->pc = (instruction & 0x0FFF);
            break;

        case 0x2000:
            // TODO
            // Calls subroutine at NNN.
            break;    

        case 0x3000:
            // TODO
            // Skip next instruction if Vx == NN (0x3XNN)
            break;

        case 0x4000:
            // TODO
            // Skip next instruction if Vx != NN (0x3XNN)
            break;

        case 0x5000:
            // TODO
            // SKip next instruction if Vx == Vy (0x5XY0)
            break;

        case 0x6000:
            // TODO 
            // Sets Vx to NN (0x6XNN)
            break;                   

        case 0x7000:
            // TODO
            break; 

        case 0x8000:
            switch (instruction & 0x000F)
            {
                case 0x0:
                    // TODO
                    break;
                case 0x1:
                    // TODO
                    break;    
                case 0x2:
                    // TODO
                    break;
                case 0x3:
                    // TODO
                    break;  
                case 0x4:
                    // TODO
                    break;
                case 0x5:
                    // TODO
                    break;
                case 0x6:
                    // TODO
                    break;
                case 0x7:
                    // TODO
                    break;  
                case 0xE:
                    // TODO
                    break;            
            }
            break;    

        case 0x9000:
            // TODO
            break; 

        case 0xA000:
            // TODO
            break; 

        case 0xB000:
            // TODO
            break; 

        case 0xC000:
            // TODO
            break; 

        case 0xD000:
            // TODO
            break; 

        case 0xE000:
            switch (instruction & 0x00FF)
            {
                case 0x009E:
                    // TODO
                    break;

                case 0x00A1:
                    // TODO
                    break;    
            }
            break;

        case 0xF000:
            switch (instruction & 0x00FF)
            {
                case 0x07:
                    // TODO
                    break;

                case 0x0A:
                    // TODO
                    break; 

                case 0x15:
                    // TODO
                    break; 

                case 0x18:
                    // TODO
                    break;

                case 0x1E:
                    // TODO
                    break; 

                case 0x29:
                    // TODO
                    break; 

                case 0x33:
                    // TODO
                    break;

                case 0x55:
                    // TODO
                    break; 

                case 0x65:
                    // TODO  
                    break;       
            }
            break;    

        default:
            err_msg(BAD_INSTRUCTION);
            break;    
    }    
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
    cpu->memory[0x023] = 0xF0;
    cpu->memory[0x024] = 0x90;
    cpu->memory[0x025] = 0xF0;
    cpu->memory[0x026] = 0x90;
    cpu->memory[0x027] = 0x90;

    // 9
    cpu->memory[0x028] = 0xF0;
    cpu->memory[0x029] = 0x90;
    cpu->memory[0x02A] = 0xF0;
    cpu->memory[0x02B] = 0x10;
    cpu->memory[0x02C] = 0xF0;

    // A
    cpu->memory[0x02D] = 0xF0;
    cpu->memory[0x02E] = 0x90;
    cpu->memory[0x02F] = 0xF0;
    cpu->memory[0x030] = 0x90;
    cpu->memory[0x031] = 0x90;

    // B
    cpu->memory[0x032] = 0xE0;
    cpu->memory[0x033] = 0x90;
    cpu->memory[0x034] = 0xE0;
    cpu->memory[0x035] = 0x90;
    cpu->memory[0x036] = 0xE0;

    // C
    cpu->memory[0x037] = 0xF0;
    cpu->memory[0x038] = 0x80;
    cpu->memory[0x039] = 0x80;
    cpu->memory[0x03A] = 0x80;
    cpu->memory[0x03B] = 0xF0;

    // D
    cpu->memory[0x03C] = 0xE0;
    cpu->memory[0x03D] = 0x90;
    cpu->memory[0x03E] = 0x90;
    cpu->memory[0x03F] = 0x90;
    cpu->memory[0x040] = 0xE0;

    // E
    cpu->memory[0x041] = 0xF0;
    cpu->memory[0x042] = 0x80;
    cpu->memory[0x043] = 0xF0;
    cpu->memory[0x044] = 0x80;
    cpu->memory[0x045] = 0xF0;

    // F
    cpu->memory[0x046] = 0xF0;
    cpu->memory[0x047] = 0x80;
    cpu->memory[0x048] = 0xF0;
    cpu->memory[0x049] = 0x80;
    cpu->memory[0x04A] = 0x80;
}
