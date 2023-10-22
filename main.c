#include "cpu.h"
#include "ram.h"
#include "test.h"

int main() {
    // Definitions
    R6502_t cpu = {0};

    // Starting Emulator
    cpu_start(&cpu);
    ram_start();
    cpu_print(cpu);

    // Loading data
    test_addr_mode(cpu);

    return 0;
}

