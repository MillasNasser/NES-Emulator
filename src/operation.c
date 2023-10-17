#include "cpu.h"
#include "hdefault.h"
#include <stdint.h>

void op_ADC(op_param_t param){
    uint8_t result = 0;
    uint8_t data = param.data;
    R6502_t *cpu = param.cpu;

    result = cpu->ACC
           + data
           + bit(cpu->STATUS.C_CARRY);

    // Updating CPU
    cpu->ACC = result;
    cpu->STATUS.Z_ZERO = result == 0;
    cpu->STATUS.N_NEGATIVE = (result&0x80) != 0;
    cpu->STATUS.V_OVERFLOW = ((result^data)&0x80) != 0;
    cpu->STATUS.C_CARRY = cpu->STATUS.V_OVERFLOW;

    *param.additional_cycle &= true;
}

void (*op_tbl[qtd_op])(op_param_t) = {0};
int load_op_tbl(){
    op_tbl[ADC] = op_ADC;
    not_imp(-1);
    op_tbl[LDA] = op_LDA;
    op_tbl[LDX] = op_LDX;
    op_tbl[LDY] = op_LDY;
    op_tbl[STA] = op_STA;
    op_tbl[STX] = op_STX;
    op_tbl[STY] = op_STY;
    op_tbl[TAX] = op_TAX;
    op_tbl[TAY] = op_TAY;
    op_tbl[TXA] = op_TXA;
    op_tbl[TYA] = op_TYA;
    op_tbl[TSX] = op_TSX;
    op_tbl[TXS] = op_TXS;
    op_tbl[PHA] = op_PHA;
    op_tbl[PHP] = op_PHP;
    op_tbl[PLA] = op_PLA;
    op_tbl[PLP] = op_PLP;
    op_tbl[AND] = op_AND;
    op_tbl[EOR] = op_EOR;
    op_tbl[ORA] = op_ORA;
    op_tbl[BIT] = op_BIT;
    op_tbl[ADC] = op_ADC;
    op_tbl[SBC] = op_SBC;
    op_tbl[CMP] = op_CMP;
    op_tbl[CPX] = op_CPX;
    op_tbl[CPY] = op_CPY;
    op_tbl[INC] = op_INC;
    op_tbl[INX] = op_INX;
    op_tbl[INY] = op_INY;
    op_tbl[DEC] = op_DEC;
    op_tbl[DEX] = op_DEX;
    op_tbl[DEY] = op_DEY;
    op_tbl[ASL] = op_ASL;
    op_tbl[LSR] = op_LSR;
    op_tbl[ROL] = op_ROL;
    op_tbl[ROR] = op_ROR;
    op_tbl[JMP] = op_JMP;
    op_tbl[JSR] = op_JSR;
    op_tbl[RTS] = op_RTS;
    op_tbl[BCC] = op_BCC;
    op_tbl[BCS] = op_BCS;
    op_tbl[BEQ] = op_BEQ;
    op_tbl[BMI] = op_BMI;
    op_tbl[BNE] = op_BNE;
    op_tbl[BPL] = op_BPL;
    op_tbl[BVC] = op_BVC;
    op_tbl[BVS] = op_BVS;
    op_tbl[CLC] = op_CLC;
    op_tbl[CLD] = op_CLD;
    op_tbl[CLI] = op_CLI;
    op_tbl[CLV] = op_CLV;
    op_tbl[SEC] = op_SEC;
    op_tbl[SED] = op_SED;
    op_tbl[SEI] = op_SEI;
    op_tbl[BRK] = op_BRK;
    op_tbl[NOP] = op_NOP;
    op_tbl[RTI] = op_RTI;

    return 0;
}
