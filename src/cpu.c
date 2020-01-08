#include "cpu.h"

void cpu_connect_bus(R6502 *cpu, Bus *bus) {
    cpu->bus = bus;
}

uint8_t cpu_read(R6502 *cpu, uint16_t addr) {
    return bus_read(cpu->bus, addr, false);
}

void cpu_write(R6502 *cpu, uint16_t addr, uint8_t data) {
    bus_write(cpu->bus, addr, data);
}