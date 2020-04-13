#include "cpu.h"

void cpu_connect_bus(R6502 *cpu, Bus *bus) {
    cpu->bus = bus;
}

//? ----------------------------------------------------------------------
//? Auxiliar
//? ----------------------------------------------------------------------

uint8_t cpu_get_val(R6502 *cpu, uint16_t addr) {
    uint8_t val = bus_read(cpu->bus, addr, false);

    return val;
}

uint8_t cpu_read(R6502 *cpu, uint16_t addr) {
    uint8_t val = bus_read(cpu->bus, addr, false);
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

    if(cpu->addr_abs & (0xFF00 != (hi << 8))){
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
        cpu->addr_abs = (cpu_read(cpu, addr & 0xFF00) << 8) | cpu_read(cpu, addr + 0);
    } else {
        // Comportamento padrão
        cpu->addr_abs = (cpu_read(cpu, addr + 1) << 8) | cpu_read(cpu, addr + 0);
    }

    return 0;
}

//? ----------------------------------------------------------------------
//? Instructions
//? ----------------------------------------------------------------------

uint8_t fetch_data(R6502 *cpu) {
    if (cpu_instr_tbl[cpu->opcode].addr_mode != Implied ){
        cpu->data = cpu_read(cpu, cpu->addr_abs);
    }

    return cpu->data;
}

uint8_t ADC(R6502 *cpu){
    uint8_t data = cpu->data;
    uint8_t acc = cpu->ACC;
    uint8_t carry = cpu->STATUS.C_CARRY;

    acc = acc + data + carry;



    return 0;
}

uint8_t AND(R6502 *cpu){
    cpu->ACC = cpu->ACC & cpu->data;

    status_t *status = &cpu->STATUS;

    status->N_NEGATIVE = (cpu->ACC & (0x80)) != 0;
    status->Z_ZERO = cpu->ACC == 0x00;

    return 1;
}

uint8_t ASL(R6502 *cpu){
    return 0;
}

uint8_t BCC(R6502 *cpu){
    return 0;
}

uint8_t BCS(R6502 *cpu){
    return 0;
}

uint8_t BEQ(R6502 *cpu){
    return 0;
}

uint8_t BIT(R6502 *cpu){
    return 0;
}

uint8_t BMI(R6502 *cpu){
    return 0;
}

uint8_t BNE(R6502 *cpu){
    return 0;
}

uint8_t BPL(R6502 *cpu){
    return 0;
}

uint8_t BRK(R6502 *cpu){
    return 0;
}

uint8_t BVC(R6502 *cpu){
    return 0;
}

uint8_t BVS(R6502 *cpu){
    return 0;
}


uint8_t CLC(R6502 *cpu){
    return 0;
}

uint8_t CLD(R6502 *cpu){
    return 0;
}

uint8_t CLI(R6502 *cpu){
    return 0;
}

uint8_t CLV(R6502 *cpu){
    return 0;
}

uint8_t CMP(R6502 *cpu){
    return 0;
}

uint8_t CPX(R6502 *cpu){
    return 0;
}

uint8_t CPY(R6502 *cpu){
    return 0;
}


uint8_t DEC(R6502 *cpu){
    return 0;
}

uint8_t DEX(R6502 *cpu){
    return 0;
}

uint8_t DEY(R6502 *cpu){
    return 0;
}


uint8_t EOR(R6502 *cpu){
    return 0;
}


uint8_t INC(R6502 *cpu){
    return 0;
}

uint8_t INX(R6502 *cpu){
    return 0;
}

uint8_t INY(R6502 *cpu){
    return 0;
}


uint8_t JMP(R6502 *cpu){
    return 0;
}

uint8_t JSR(R6502 *cpu){
    return 0;
}


uint8_t LDA(R6502 *cpu){
    return 0;
}

uint8_t LDX(R6502 *cpu){
    return 0;
}

uint8_t LDY(R6502 *cpu){
    return 0;
}

uint8_t LSR(R6502 *cpu){
    return 0;
}


uint8_t NOP(R6502 *cpu){
    return 0;
}


uint8_t ORA(R6502 *cpu){
    return 0;
}


uint8_t PHA(R6502 *cpu){
    return 0;
}

uint8_t PHP(R6502 *cpu){
    return 0;
}

uint8_t PLA(R6502 *cpu){
    return 0;
}

uint8_t PLP(R6502 *cpu){
    return 0;
}


uint8_t ROL(R6502 *cpu){
    return 0;
}

uint8_t ROR(R6502 *cpu){
    return 0;
}

uint8_t RTI(R6502 *cpu){
    return 0;
}

uint8_t RTS(R6502 *cpu){
    return 0;
}


uint8_t SBC(R6502 *cpu){
    return 0;
}

uint8_t SEC(R6502 *cpu){
    return 0;
}

uint8_t SED(R6502 *cpu){
    return 0;
}

uint8_t SEI(R6502 *cpu){
    return 0;
}

uint8_t STA(R6502 *cpu){
    return 0;
}

uint8_t STX(R6502 *cpu){
    return 0;
}

uint8_t STY(R6502 *cpu){
    return 0;
}


uint8_t TAX(R6502 *cpu){
    return 0;
}

uint8_t TAY(R6502 *cpu){
    return 0;
}

uint8_t TSX(R6502 *cpu){
    return 0;
}

uint8_t TXA(R6502 *cpu){
    return 0;
}

uint8_t TXS(R6502 *cpu){
    return 0;
}

uint8_t TYA(R6502 *cpu){
    return 0;
}
