#include "bus.h"

uint8_t bus_read(Bus *bus, uint16_t addr, bool b_read_only){
    if(addr >= 0x0000 && addr <= 0xffff){
        return bus->RAM[addr];
    }

    return 0x00;
}

void bus_write(Bus *bus, uint16_t addr, uint8_t data){
    if(addr >= 0x0000 && addr <= 0xffff){
        bus->RAM[addr] = data;
    }
}
