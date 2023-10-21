#include "cpu.h"
#include "ram.h"
#include <stdint.h>

int main() {
    // Definitions
    R6502_t cpu = {0};

    // Starting Emulator
    cpu_start(&cpu);
    ram_start();

    // Loading data



    // Testes no processo
    // cpu_print(cpu);

    exec(&cpu, 0x69);
    // cpu_print(cpu);

    ram_write(0x0420, 69);
    exec(&cpu, 0x6D);
    // cpu_print(cpu);

    ram_write(0x042, 100);
    exec(&cpu, 0x65);
    // cpu_print(cpu);

    ram_write(0x043, 1);
    cpu.X = 1;
    exec(&cpu, 0x75);
    cpu_print(cpu);

    return 0;
}

