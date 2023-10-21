#ifndef __NES_RAM__
#define __NES_RAM__
    #include "hdefault.h"

    // Constants
    #define RAM_SIZE 0xFFFF
    
    // Errors
    // #define ERR_RAM_NOT_LOADED -200
    
    extern uint8_t ram[RAM_SIZE];
    int ram_start();

    uint8_t ram_read(uint16_t addr);
    uint8_t ram_write(uint16_t addr, uint8_t data);
#endif // __NES_RAM__
