#include "cpu.h"

void cpu_connect_bus(R6502 *cpu, Bus *bus) {
    cpu->bus = bus;
}

//? ----------------------------------------------------------------------
//? Auxiliar
//? ----------------------------------------------------------------------

uint8_t cpu_get_val(R6502 *cpu, uint16_t addr) {
    uint8_t val = valbus_read(cpu->bus, addr, false);

    return val;
}

uint8_t cpu_read(R6502 *cpu, uint16_t addr) {
    uint8_t val = valbus_read(cpu->bus, addr, false);
    cpu->PC++;

    return val;
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
uint8_t Accum(R6502 *cpu){
    cpu->addr_abs = cpu->ACC;

    return 0;
}

uint8_t IMM(R6502 *cpu){
    cpu->addr_abs = cpu->PC++;

    return 0;
}

uint8_t Abs(R6502 *cpu){
    uint16_t lo = cpu_read(cpu, cpu->PC);
    uint16_t hi = cpu_read(cpu, cpu->PC);

    cpu->addr_abs = (hi << 8) | lo;

    return 0;
}

uint8_t ZP(R6502 *cpu){
    uint16_t addr = cpu_read(cpu, cpu->PC);

    cpu->addr_abs = addr & 0x00FF;

    return 0;
}

uint8_t ZPX(R6502 *cpu){
    uint16_t addr = cpu_read(cpu, cpu->PC);

    cpu->addr_abs = (addr + cpu->X) & 0x00FF;

    return 0;
}

uint8_t ZPY(R6502 *cpu){
    uint16_t addr = cpu_read(cpu, cpu->PC);

    cpu->addr_abs = (addr + cpu->Y) & 0x00FF;

    return 0;
}

uint8_t ABSX(R6502 *cpu){
    uint8_t hi, lo;
    lo = cpu_read(cpu, cpu->PC);
    hi = cpu_read(cpu, cpu->PC);

    uint16_t addr = (hi << 8) + lo;
    addr += cpu->X;

    cpu->addr_abs = addr;

    // Se houver trocado o bit, indica troca de pagina
    if ((addr && 0xFF00) != (hi << 8)) {
        return 1;
    } else {
        return 0;
    }
}

uint8_t ABSY(R6502 *cpu){
        uint8_t hi, lo;
    lo = cpu_read(cpu, cpu->PC);
    hi = cpu_read(cpu, cpu->PC);

    uint16_t addr = (hi << 8) + lo;
    addr += cpu->Y;

    cpu->addr_abs = addr;

    // Se houver trocado o bit, indica troca de pagina
    if ((addr && 0xFF00) != (hi << 8)) {
        return 1;
    } else {
        return 0;
    }
}

uint8_t Implied(R6502 *cpu){
    cpu->data = cpu->ACC;

    return 0;
}

uint8_t Relative(R6502 *cpu){
    uint16_t addr_rel = cpu_read(cpu, cpu->PC);
    cpu->PC++;

    if (addr_rel & 0x80) {
        addr_rel |= 0xFF00;
    }

    cpu->addr_rel = addr_rel;

    return 0;
}

uint8_t INDX(R6502 *cpu){
    uint16_t addr = cpu_read(cpu, cpu->PC);

    uint8_t lo = cpu_read(cpu, (addr + cpu->X) & 0x00FF);
    uint8_t hi = cpu_read(cpu, (addr + cpu->X + 1) & 0x00FF);

    cpu->addr_abs = (hi << 8) + lo;

    return 0;
}

uint8_t INDY(R6502 *cpu){
    uint16_t addr = cpu_read(cpu, cpu->PC);

    uint8_t lo = cpu_read(cpu, addr & 0x00ff);
    uint8_t hi = cpu_read(cpu, (addr + 1) & 0x00ff);

    cpu->addr_abs = (hi << 8) + lo;
    cpu->addr_abs += cpu->Y;

    if(cpu->addr_abs & 0xFF00 != (hi << 8)){
        return 1;
    } else {
        return 0;
    }
}

uint8_t IND(R6502 *cpu){
    uint8_t lo = cpu_read(cpu, cpu->PC);
    uint8_t hi = cpu_read(cpu, cpu->PC);

    uint16_t addr = (hi << 8) + lo;

    if (lo == 0x00FF){
        // Simula bug de limite de paginação
		cpu->addr_abs = (read(addr & 0xFF00) << 8) | read(addr + 0);
	} else {
        // Comportamento padrão
		cpu->addr_abs = (read(addr + 1) << 8) | read(addr + 0);
	}

	return 0;

}

//? ----------------------------------------------------------------------
//? Addressing modes
//? ----------------------------------------------------------------------