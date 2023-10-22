
#include "ram.h"
#include <stdint.h>

uint8_t ram[RAM_SIZE];
int ram_start(){
    memset(&ram, 0, sizeof(uint8_t)*RAM_SIZE);

    return true;
}

uint8_t ram_read(uint16_t addr) {
    return ram[addr];
}

uint8_t ram_write(uint16_t addr, uint8_t data) {
    ram[addr] = data;

    return true;
}

