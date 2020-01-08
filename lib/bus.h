#if !defined(_NES_BUS_)
#define _NES_BUS_

    //? Includes
    #include "hdefault.h"
    
    typedef struct bus_t{
        uint8_t RAM[64 * 1024];
    } Bus;
    
    uint8_t bus_read(Bus *bus, uint16_t addr, bool b_read_only);
    void bus_write(Bus *bus, uint16_t addr, uint8_t data);

#endif // _NES_BUS_
