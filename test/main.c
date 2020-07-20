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

    result = test_2nnn();
    if (result == FAIL)
    {
        print_error("test_2nnn failed");
    } else {
        print_good("test_2nnn passed");
    }

    result = test_3xkk();
    if (result == FAIL)
    {
        print_error("test_3xkk failed");
    } else {
        print_good("test_3xkk passed");
    }

    result = test_4xkk();
    if (result == FAIL)
    {
        print_error("test_4xkk failed");
    } else {
        print_good("test_4xkk passed");
    }

    result = test_5xy0();
    if (result == FAIL)
    {
        print_error("test_5xy0 failed");
    } else {
        print_good("test_5xy0 passed");
    }

    result = test_6xkk();
    if (result == FAIL)
    {
        print_error("test_6xkk failed");
    } else {
        print_good("test_6xkk passed");
    }

    result = test_7xkk();
    if (result == FAIL)
    {
        print_error("test_7xkk failed");
    } else {
        print_good("test_7xkk passed");
    }

    result = test_8xy0();
    if (result == FAIL)
    {
        print_error("test_8xy0 failed");
    } else {
        print_good("test_8xy0 passed");
    }

    result = test_8xy1();
    if (result == FAIL)
    {
        print_error("test_8xy1 failed");
    } else {
        print_good("test_8xy1 passed");
    }

    result = test_8xy2();
    if (result == FAIL)
    {
        print_error("test_8xy2 failed");
    } else {
        print_good("test_8xy2 passed");
    }

    result = test_8xy3();
    if (result == FAIL)
    {
        print_error("test_8xy3 failed");
    } else {
        print_good("test_8xy3 passed");
    }

    result = test_8xy4();
    if (result == FAIL)
    {
        print_error("test_8xy4 failed");
    } else {
        print_good("test_8xy4 passed");
    }

    result = test_8xy5();
    if (result == FAIL)
    {
        print_error("test_8xy5 failed");
    } else {
        print_good("test_8xy5 passed");
    }

    result = test_8xy6();
    if (result == FAIL)
    {
        print_error("test_8xy6 failed");
    } else {
        print_good("test_8xy6 passed");
    }

    result = test_8xy7();
    if (result == FAIL)
    {
        print_error("test_8xy7 failed");
    } else {
        print_good("test_8xy7 passed");
    }

    result = test_8xyE();
    if (result == FAIL)
    {
        print_error("test_8xyE failed");
    } else {
        print_good("test_8xyE passed");
    }

    result = test_9xy0();
    if (result == FAIL)
    {
        print_error("test_9xy0 failed");
    } else {
        print_good("test_9xy0 passed");
    }

    result = test_Annn();
    if (result == FAIL)
    {
        print_error("test_Annn failed");
    } else {
        print_good("test_Annn passed");
    }

    result = test_Bnnn();
    if (result == FAIL)
    {
        print_error("test_Bnnn failed");
    } else {
        print_good("test_Bnnn passed");
    }

    result = test_Cxkk();
    if (result == FAIL)
    {
        print_error("test_Cxkk failed");
    } else {
        print_good("test_Cxkk passed");
    }

    result = test_Dxyn();
    if (result == FAIL)
    {
        print_error("test_Dxyn failed");
    } else {
        print_good("test_Dxyn passed");
    }

    result = test_Ex9E();
    if (result == FAIL)
    {
        print_error("test_Ex9E failed");
    } else {
        print_good("test_Ex9E passed");
    }

    result = test_ExA1();
    if (result == FAIL)
    {
        print_error("test_ExA1 failed");
    } else {
        print_good("test_ExA1 passed");
    }

    result = test_Fx07();
    if (result == FAIL)
    {
        print_error("test_Fx07 failed");
    } else {
        print_good("test_Fx07 passed");
    }

    result = test_Fx0A();
    if (result == FAIL)
    {
        print_error("test_Fx0A failed");
    } else {
        print_good("test_Fx0A passed");
    }

    result = test_Fx15();
    if (result == FAIL)
    {
        print_error("test_Fx15 failed");
    } else {
        print_good("test_Fx15 passed");
    }

    result = test_Fx18();
    if (result == FAIL)
    {
        print_error("test_Fx18 failed");
    } else {
        print_good("test_Fx18 passed");
    }

    result = test_Fx1E();
    if (result == FAIL)
    {
        print_error("test_Fx1E failed");
    } else {
        print_good("test_Fx1E passed");
    }

    result = test_Fx29();
    if (result == FAIL)
    {
        print_error("test_Fx29 failed");
    } else {
        print_good("test_Fx29 passed");
    }

    result = test_Fx33();
    if (result == FAIL)
    {
        print_error("test_Fx33 failed");
    } else {
        print_good("test_Fx33 passed");
    }

    result = test_Fx55();
    if (result == FAIL)
    {
        print_error("test_Fx55 failed");
    } else {
        print_good("test_Fx55 passed");
    }

    result = test_Fx65();
    if (result == FAIL)
    {
        print_error("test_Fx65 failed");
    } else {
        print_good("test_Fx65 passed");
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

Result test_2nnn()
{
    CPU cpu;
    cpu_init(&cpu);

    Opcode instruction = 0x20FF;
    cpu.pc = 0x210;

    perform_instruction(&cpu, instruction);

    return cpu.pc = 0x0FF && cpu.sp == 1 && cpu.stack[0] == 0x210;
}

Result test_3xkk()
{
    CPU cpu;
    cpu_init(&cpu);

    cpu.pc = 2;
    cpu.registers[0x5] = 0x2A;
    Opcode instruction = 0x352A;
    perform_instruction(&cpu, instruction);

    return cpu.pc == 4;    
}

Result test_4xkk()
{
    CPU cpu;
    cpu_init(&cpu);

    cpu.pc = 2;
    cpu.registers[0x5] = 0x2A;
    Opcode instruction = 0x452B;
    perform_instruction(&cpu, instruction);

    return cpu.pc == 4;    
}

Result test_5xy0()
{
    CPU cpu;
    cpu_init(&cpu);

    cpu.pc = 2;
    cpu.registers[0x5] = 0x2A;
    cpu.registers[0x6] = 0x2A;
    Opcode instruction = 0x5560;
    perform_instruction(&cpu, instruction);

    return cpu.pc == 4;     
}

Result test_6xkk()
{
    CPU cpu;
    cpu_init(&cpu);

    Opcode instruction = 0x651A;
    perform_instruction(&cpu, instruction);

    return cpu.registers[5] == 0x1A;   
}

Result test_7xkk()
{
    CPU cpu;
    cpu_init(&cpu);

    cpu.registers[5] = 0x2B;

    Opcode instruction = 0x751A;
    perform_instruction(&cpu, instruction);

    return cpu.registers[5] == 0x45;   
}

Result test_8xy0()
{
    CPU cpu;
    cpu_init(&cpu);

    cpu.registers[5] = 0x2C;
    cpu.registers[6] = 0x1A;

    Opcode instruction = 0x8560;
    perform_instruction(&cpu, instruction);

    return cpu.registers[5] == 0x1A;   
}

Result test_8xy1()
{
    CPU cpu;
    cpu_init(&cpu);

    cpu.registers[1] = 0xAA;    // 10101010
    cpu.registers[2] = 0x55;    // 01010101

    Opcode instruction = 0x8121;
    perform_instruction(&cpu, instruction);

    return cpu.registers[1] == 0xFF;     
}

Result test_8xy2()
{
    CPU cpu;
    cpu_init(&cpu);

    cpu.registers[1] = 0xAA;    // 10101010
    cpu.registers[2] = 0x55;    // 01010101

    Opcode instruction = 0x8122;
    perform_instruction(&cpu, instruction);

    return cpu.registers[1] == 0x00;  
}

Result test_8xy3()
{
    CPU cpu;
    cpu_init(&cpu);

    cpu.registers[1] = 0xCB;    // 11001010
    cpu.registers[2] = 0xB5;    // 10110101

    Opcode instruction = 0x8123;
    perform_instruction(&cpu, instruction);

    return cpu.registers[1] == 0x7E;   
}

Result test_8xy4()
{
    CPU cpu;
    cpu_init(&cpu);

    cpu.registers[1] = 0x82;    // 130
    cpu.registers[2] = 0x8C;    // 140

    Opcode instruction = 0x8124;
    perform_instruction(&cpu, instruction);

    return cpu.registers[1] == 0x0E && cpu.registers[0xF] == 1;    
}

Result test_8xy5()
{
    CPU cpu;
    cpu_init(&cpu);

    cpu.registers[1] = 0x8C;    // 140
    cpu.registers[2] = 0x82;    // 130

    Opcode instruction = 0x8125;
    perform_instruction(&cpu, instruction);

    return cpu.registers[1] == 0x0A && cpu.registers[0xF] == 1; 
}

Result test_8xy6()
{
    CPU cpu;
    cpu_init(&cpu);

    cpu.registers[1] = 0x05;    // odd, so least sig fig is 1

    Opcode instruction = 0x8106;
    perform_instruction(&cpu, instruction);

    return cpu.registers[1] == 0x02 && cpu.registers[0xF] == 1;    
}

Result test_8xy7()
{
    CPU cpu;
    cpu_init(&cpu);

    cpu.registers[1] = 0x82;    // 130
    cpu.registers[2] = 0x8C;    // 140

    Opcode instruction = 0x8127;
    perform_instruction(&cpu, instruction);

    return cpu.registers[1] == 0x0A && cpu.registers[0xF] == 1; 
}

Result test_8xyE()
{
    CPU cpu;
    cpu_init(&cpu);

    cpu.registers[1] = 0x80;    // 128

    Opcode instruction = 0x812E;
    perform_instruction(&cpu, instruction);

    return cpu.registers[1] == 0x0 && cpu.registers[0xF] == 1; 
}

Result test_9xy0()
{
    CPU cpu;
    cpu_init(&cpu);

    return FAIL;    
}

Result test_Annn()
{
    CPU cpu;
    cpu_init(&cpu);

    return FAIL;    
}

Result test_Bnnn()
{
    CPU cpu;
    cpu_init(&cpu);

    return FAIL;    
}

Result test_Cxkk()
{
    CPU cpu;
    cpu_init(&cpu);

    return FAIL;    
}

Result test_Dxyn()
{
    CPU cpu;
    cpu_init(&cpu);

    return FAIL;    
}

Result test_Ex9E()
{
    CPU cpu;
    cpu_init(&cpu);

    return FAIL;    
}

Result test_ExA1()
{
    CPU cpu;
    cpu_init(&cpu);

    return FAIL;    
}

Result test_Fx07()
{
    CPU cpu;
    cpu_init(&cpu);

    return FAIL;    
}

Result test_Fx0A()
{
    CPU cpu;
    cpu_init(&cpu);

    return FAIL;    
}

Result test_Fx15()
{
    CPU cpu;
    cpu_init(&cpu);

    return FAIL;    
}

Result test_Fx18()
{
    CPU cpu;
    cpu_init(&cpu);

    return FAIL;    
}

Result test_Fx1E()
{
    CPU cpu;
    cpu_init(&cpu);

    return FAIL;    
}

Result test_Fx29()
{
    CPU cpu;
    cpu_init(&cpu);

    return FAIL;    
}

Result test_Fx33()
{
    CPU cpu;
    cpu_init(&cpu);

    return FAIL;    
}

Result test_Fx55()
{
    CPU cpu;
    cpu_init(&cpu);

    return FAIL;    
}

Result test_Fx65()
{
    CPU cpu;
    cpu_init(&cpu);

    return FAIL;    
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
