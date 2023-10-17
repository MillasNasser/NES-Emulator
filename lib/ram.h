#ifndef __NES_RAM__
#define __NES_RAM__
    #include "hdefault.h"

    // Constants
    #define RAM_SIZE 0xFFFF
    
    // Errors
    #define ERR_RAM_NOT_LOADED -200
    
    typedef struct {
        uint8_t address[RAM_SIZE];
    } nes_ram_t;

    uint8_t ram_read(uint16_t addr);
    uint8_t ram_write(uint16_t addr);
#endif // __NES_RAM__
