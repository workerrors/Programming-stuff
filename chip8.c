#include <stdio.h>
#include <stdint.h>
#include <string.h>


typedef struct {
        uint8_t v[16]; // Registers - 16 generap purpose 8-bit
        uint8_t memory[4096]; // Memory, 4KB ram
        uint16_t I; // Index register (Stores memory addresses)
        uint16_t PC; // program counter, Which instructions to do next
        uint16_t Stack[16]; // Stockpile for PC, to return to previous addresses
        uint8_t SP; // To locate specific addresses in the stockpile 

        // Timer starts from 60 hertz, to 0
        uint8_t sound_timer; // For sound effects
        uint8_t delay_timer; // For game events
        uint8_t display[64 * 32]; // resolution
        uint8_t keypad[16]; // RTrack which of the hex keys are pressed down
    } CPU;


// Passed struct memory address to variable pointer for easier use
void cpu_start(CPU *cpu) {

    // Sets memory value to 0 to avoid
    // leftover bytes from processes causing problems 
    memset(cpu, 0, sizeof(CPU));
    // Set PC starting value to 512 bytes to have reserved space for system data, like fonts
    cpu->PC = 0x200;





        // Declare font
    uint8_t fontset[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    // COunts from 0-80 for the 80 font bytes
    for (int i = 0; i < 80; i++ )
    // As it counts starting from byte 80, it loops and
    // adds the fontset [i] as well 
    {
    cpu->memory[0x050 + i] = fontset [i];
    }


    }


// Cycle for caluclations
void cpu_cycle(CPU *cpu) {
    // Takes 2 8-bits and merges into one 16-bit 
    uint16_t opcode = (cpu->memory[cpu->PC] << 8) | cpu->memory[cpu->PC + 1];

    // Move PC two steps forward
    cpu->PC += 2;

    // Snatches second number, and last 2 digits of the opcode 
    uint8_t X = (opcode & 0x0F00) >> 8; 

    uint8_t NN = opcode & 0x00FF;

    
    switch (opcode & 0xF000) { 
        case 0x6000: 
            
            cpu->v[X] = NN;
            break;
        
        case 0x7000: 
            cpu->v[X] += NN;
            break;
           } 

        }

    // out of place implementation of the cpu_load_rom function 
    /*
    int cpu_load_rom(CPU *cpu , const char *filename) {
        FILE *f = fopen(filename, "rb");
        if (!f) {
            perror("Failed to open ROM file");
            return 1;
        }
        fread(&cpu->memory[0x200], 1, 4096 - 0x200, f);
        fclose(f);
        return 0;
        
    } */





int main(void)
{
    // Creates the struct in memory
    CPU hot_cpu;

    // Call cpu_start function and grab hot_cpu address to initialise
    cpu_start(&hot_cpu);

}



