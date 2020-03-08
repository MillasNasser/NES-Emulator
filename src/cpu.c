#include "cpu.h"

void cpu_connect_bus(R6502 *cpu, Bus *bus) {
    cpu->bus = bus;
}

//? ----------------------------------------------------------------------
//? Auxiliar
//? ----------------------------------------------------------------------

uint8_t cpu_read(R6502 *cpu, uint16_t addr) {
    return bus_read(cpu->bus, addr, false);
}

void cpu_write(R6502 *cpu, uint16_t addr, uint8_t data) {
    bus_write(cpu->bus, addr, data);
}

//? ----------------------------------------------------------------------
//? Signals
//? ----------------------------------------------------------------------

void clock(const signal_param_t *p) {
    uint8_t opcode = 0;
    uint8_t cycles = 0;
    instruction_t op = NO_INSTR;

    if(p->cpu->cycles == 0) {
        opcode = cpu_read(p->cpu, p->cpu->PC);
        p->cpu->opcode = opcode;

        p->cpu->PC++;

        // Pegando o número de ciclos da instrução
        instruction_t op = cpu_instr_tbl[opcode];

        cycles = op.cycles;

        // Operação
        uint8_t add_cy1 = op.addr_mode();
        uint8_t add_cy2 = op.op();

        cycles += (add_cy1 & add_cy2);
        p->cpu->cycles = cycles;
    }

    // Executando a operação
    p->cpu->cycles--;
}

//? ----------------------------------------------------------------------
//? Addressing modes
//? ----------------------------------------------------------------------
uint8_t Accum(const addrmod_param_t *p){

}

uint8_t IMM(const addrmod_param_t *p){
    p->cpu->addr_abs = p->cpu->PC++;

    return 0;
}

uint8_t Abs(const addrmod_param_t *p){

    uint16_t lo = cpu_read(p->cpu, p->cpu->PC);
    p->cpu, p->cpu->PC++;

    uint16_t hi = cpu_read(p->cpu, p->cpu->PC);
    p->cpu, p->cpu->PC++;

    p->cpu->addr_abs = (hi << 8) | lo;

    return 0;
}

uint8_t ZP(const addrmod_param_t *p){
    uint16_t addr = cpu_read(p->cpu, p->cpu->PC);
    p->cpu->PC++;

    p->cpu->addr_abs = addr & 0x00FF;

    return 0;
}

uint8_t ZPX(const addrmod_param_t *p){
    uint16_t addr = cpu_read(p->cpu, p->cpu->PC);

    p->cpu->PC++;

    p->cpu->addr_abs = (addr + p->cpu->X) & 0x00FF;

    return 0;
}

uint8_t ZPY(const addrmod_param_t *p){
    uint16_t addr = cpu_read(p->cpu, p->cpu->PC);

    p->cpu->PC++;

    p->cpu->addr_abs = (addr + p->cpu->Y) & 0x00FF;

    return 0;
}

uint8_t ABSX(const addrmod_param_t *p){
    uint8_t hi, lo;
    lo = cpu_read(p->cpu, p->)
}

uint8_t ABSY(const addrmod_param_t *p){

}

uint8_t Implied(const addrmod_param_t *p){
    p->cpu->data = p->cpu->ACC;
    return 0;
}

uint8_t Relative(const addrmod_param_t *p){
    uint16_t addr_rel = cpu_read(p->cpu, p->cpu->PC);
    p->cpu->PC++;

    if (addr_rel & 0x80) {
        addr_rel |= 0xFF00;
    }

    p->cpu->addr_rel = addr_rel;

    return 0;
}

uint8_t INDX(const addrmod_param_t *p){

}

uint8_t INDY(const addrmod_param_t *p){

}

uint8_t IND(const addrmod_param_t *p){

}
