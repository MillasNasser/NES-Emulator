#if !defined(_CPU_INSTRUCTION_TABLE_)
#define _CPU_INSTRUCTION_TABLE_

    #include "cpu.h"

    #define NO_INSTR ((instruction_t){"???", NULL, NULL, 0})

    typedef struct {
        const char name[8];
        uint8_t (*op)();
        uint8_t (*addr_mode)();
        uint8_t cycles;
    } instruction_t;

    instruction_t cpu_instr_tbl[256];

#endif // _CPU_INSTRUCTION_TABLE_