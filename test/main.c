#include "main.h"

int main(int argc, char **argv)
{
    printf("Running chip8 tests...\n");
    
    Result result;

    result = test_00E0();
    if (result == FAIL)
    {
        print_error("test_00E0 failed");
    } else {
        print_good("test_00E0 passed");
    }

    result = test_00EE();
    if (result == FAIL)
    {
        print_error("test_00EE failed");
    } else {
        print_good("test_00EE passed");
    }

    result = test_1nnn();
    if (result == FAIL)
    {
        print_error("test_1nnn failed");
    } else {
        print_good("test_1nnn passed");
    }
}

/*
    Tests the 00E0 Opcode
*/
Result test_00E0()
{
    CPU cpu;
    cpu_init(&cpu);
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            cpu.display[i][j] = 1;
        }
    }

    Opcode instruction = 0x00E0;
    perform_instruction(&cpu, instruction);

    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            if (cpu.display[i][j] != 0) {
                return FAIL;
            }
        }
    }
    return PASS;
}

Result test_00EE()
{
    CPU cpu;
    cpu_init(&cpu);
    Opcode instruction = 0x00EE;
    cpu.stack[0] = 0xFFF;
    cpu.sp = 1;

    perform_instruction(&cpu, instruction);

    return cpu.pc == 0xFFF && cpu.sp == 0;
}

Result test_1nnn()
{
    CPU cpu;
    cpu_init(&cpu);
    // ROM which should jump to memory location
    FILE *rom = fopen("test_roms/1nnn_test_rom.ch8", "r");
    load_rom(&cpu, rom);
    process_cycle(&cpu);
    // if memory location was changed properly, next instruction should be
    // wiping the display
    Opcode instruction = get_next_instruction(&cpu);
    return instruction == 0x00E0;
}

void print_error(char *string)
{
    printf("\033[1;31m");
    printf("%s\n", string);
}

void print_good(char *string)
{
    printf("\033[1;32m");
    printf("%s\n", string);
}

// utility
void print_display(CPU* cpu)
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            printf("%02x ", cpu->display[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n\n");
}
