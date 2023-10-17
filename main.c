#include "cpu.h"
#include <stdint.h>
#include <stdio.h>

int main() {
    R6502_t cpu = {0};
    cpu_start(&cpu);
    cpu_print(cpu);

    exec(&cpu, 0x69);
    cpu_print(cpu);

    return 0;
}

