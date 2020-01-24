#if !defined(_CPU_INSTRUCTION_TABLE_)
#define _CPU_INSTRUCTION_TABLE_

    #include "cpu.h"

    #define NO_INSTR ((instruction_t){"???", NULL, NULL, 0})

    extern instruction_t cpu_instr_tbl[256];

#endif // _CPU_INSTRUCTION_TABLE_