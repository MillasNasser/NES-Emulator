#include "cpu.h"
#include "hdefault.h"
#include "ram.h"
#include <stdint.h>
#include <stdio.h>

int cpu_start(R6502_t *cpu){
    cpu->STATUS.U_UNABLE = 1;
    cpu->STK = (uint8_t)STACK_START;

    load_op_tbl();
    load_addr_tbl();

    cpu_load_instr(cpu);

    return 0;
}

uint8_t fetch(R6502_t *cpu) {
    uint8_t data = ram_read(cpu->PC);
    cpu->PC++;

    return data;
}

void cpu_print(R6502_t proc){
    printf("-----====== CPU ======-----\n");
    printf("[TIME] cycles: %d\n", proc.cycles);
    printf("[PROG] PC: %d\n", proc.PC);
    printf("[MEMO] stack: 0x%02x\n", proc.STK);
    printf("[REG] X  : 0x%02x | %d \n", proc.X, proc.X);
    printf("[REG] Y  : 0x%02x | %d \n", proc.Y, proc.Y);
    printf("[REG] ACC: 0x%02x | %d \n", proc.ACC, proc.ACC);
    printf("[STATUS] NVUBDIZC | status\n");
    printf("[STATUS] %u%u%u%u%u%u%u%u | %u\n",
        proc.STATUS.N_NEGATIVE & 0x01,
        proc.STATUS.V_OVERFLOW & 0x01,
        proc.STATUS.U_UNABLE & 0x01,
        proc.STATUS.B_BRK & 0x01,
        proc.STATUS.D_DECIMAL & 0x01,
        proc.STATUS.I_IRQ_DISABLE & 0x01,
        proc.STATUS.Z_ZERO & 0x01,
        proc.STATUS.C_CARRY & 0x01,
        proc.STATUS.status
    );
    printf("-----=================-----\n");
}

int exec(R6502_t *cpu, uint8_t op_code) {
    if( cpu == NULL ) error("CPU not started during exec command", ERR_CPU_NOT_LOADED);

    cpuinst_t inst = cpu->instr[op_code];
    void (*func_addr)(addr_param_t) = addr_tbl[ inst.addr_mode ];
    void (*func_op)(op_param_t) = op_tbl[ inst.op ];

    uint16_t data = 0;
    uint8_t req_cycle = 0;
    bool is_memory = true;

    // Retrieving data or address
    if (func_addr == addr_implied) is_memory = false;
    if (func_addr == addr_immediate) is_memory = false;
    if (func_addr == addr_accumulator) is_memory = false;
    
    func_addr((addr_param_t){
        .cpu = cpu,
        .data = &data,
        .additional_cycle = &req_cycle,
    });

    func_op((op_param_t){
        .cpu = cpu,
        .data = data,
        .is_memory = is_memory,
        .additional_cycle = &req_cycle
    });

    // Updating CPU needed cycles
    cpu->cycles = inst.cycles + req_cycle;

    return 0;
}

int cpu_load_instr(R6502_t *cpu) {
    int result = 0;
    
    cpu->instr[0x69] = (cpuinst_t){.op=ADC, .size=2, .cycles=2, .addr_mode=immediate };
    cpu->instr[0x65] = (cpuinst_t){.op=ADC, .size=2, .cycles=3, .addr_mode=zero_page };
    cpu->instr[0x75] = (cpuinst_t){.op=ADC, .size=2, .cycles=4, .addr_mode=zero_page_x };
    cpu->instr[0x6D] = (cpuinst_t){.op=ADC, .size=3, .cycles=4, .addr_mode=absolute };
    cpu->instr[0x7D] = (cpuinst_t){.op=ADC, .size=3, .cycles=4, .addr_mode=absolute_x }; // +1
    cpu->instr[0x79] = (cpuinst_t){.op=ADC, .size=3, .cycles=4, .addr_mode=absolute_y }; // +1
    cpu->instr[0x61] = (cpuinst_t){.op=ADC, .size=2, .cycles=6, .addr_mode=indirect_x };
    cpu->instr[0x71] = (cpuinst_t){.op=ADC, .size=2, .cycles=5, .addr_mode=indirect_y }; // +1
    not_imp(result);
};



