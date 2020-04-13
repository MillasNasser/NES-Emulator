#include "hdefault.h"

#include "cpu.h"

int main() {

    R6502 cpu = {0};

    cpu.data = 8;
    cpu.ACC = 15;

    printf("Accumulador %d; Dados %d\n", cpu.ACC, cpu.data);

    printf("Pode pedir ciclo? %s\n", AND(&cpu)?"Sim":"Nao");

    printf("Accumulador %d; Dados %d\n", cpu.ACC, cpu.data);

    return 0;
}

