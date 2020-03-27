#if !defined(_NES_CPU_)
#define _NES_CPU_

    /**
     * Data bus has 8bit length
     * Address bus has 16bits length
     * Bus enable (BE)
     * Interrupt Request (IRQ)
     *
    */

    // Bus

    //? Includes
    #include "hdefault.h"
    #include "cpu_instrtbl.h"
    #include "bus.h"

    enum STATUS_REG{
        C_CARRY       = (1 << 0),
        Z_ZERO        = (1 << 1),
        I_IRQ_DISABLE = (1 << 2),
        D_DECIMAL     = (1 << 3),
        B_BRK         = (1 << 4),
        U_UNABLE      = (1 << 5),
        V_OVERFLOW    = (1 << 6),
        N_NEGATIVE    = (1 << 7),
    };

    typedef struct R6502{
        struct bus_t *bus;
        struct R6502 *self;

        uint8_t cycles;
        uint8_t opcode;

        //* Dados R/W no Bus
        uint8_t data;
        uint16_t addr_abs;
        uint16_t addr_rel;


        //* Registers
        uint8_t ACC; // Accumulator
        uint8_t X; // Index Register X
        uint8_t Y; // Index Register Y
        uint8_t STK; // Stack pointer
        uint8_t STATUS; // Status Reg
        uint16_t PC; // Program Counter

    } R6502;

    void cpu_connect_bus(R6502 *cpu, Bus *bus);

    uint8_t cpu_get_val(R6502 *cpu, uint16_t addr);
    uint8_t cpu_read(R6502 *cpu, uint16_t addr);
    void cpu_write(R6502 *cpu, uint16_t addr, uint8_t data);

    //? Signals
    typedef struct {
        R6502 *cpu;
    }signal_param_t;

    void clock(const signal_param_t *param);
    void RDY(const signal_param_t *param);
    void IRQ(const signal_param_t *param);
    void NMI(const signal_param_t *param);
    void SO(const signal_param_t *param);
    void RES(const signal_param_t *param);

    //? Addressing modes
    #define addrmod_param R6502 *cpu

    uint8_t Accum( addrmod_param );
    uint8_t IMM( addrmod_param );
    uint8_t Abs( addrmod_param );
    uint8_t ZP( addrmod_param );
    uint8_t ZPX( addrmod_param );
    uint8_t ZPY( addrmod_param );
    uint8_t ABSX( addrmod_param );
    uint8_t ABSY( addrmod_param );
    uint8_t Implied( addrmod_param );
    uint8_t Relative( addrmod_param );
    uint8_t INDX( addrmod_param );
    uint8_t INDY( addrmod_param );
    uint8_t IND( addrmod_param );

    //? Intructions
    typedef struct {
        R6502 *cpu;
    } instr_param_t;

    uint8_t ADC(const instr_param_t *param);
    uint8_t AND(const instr_param_t *param);
    uint8_t ASL(const instr_param_t *param);

    uint8_t BCC(const instr_param_t *param);
    uint8_t BCS(const instr_param_t *param);
    uint8_t BEQ(const instr_param_t *param);
    uint8_t BIT(const instr_param_t *param);
    uint8_t BMI(const instr_param_t *param);
    uint8_t BNE(const instr_param_t *param);
    uint8_t BPL(const instr_param_t *param);
    uint8_t BRK(const instr_param_t *param);
    uint8_t BVC(const instr_param_t *param);
    uint8_t BVS(const instr_param_t *param);

    uint8_t CLC(const instr_param_t *param);
    uint8_t CLD(const instr_param_t *param);
    uint8_t CLI(const instr_param_t *param);
    uint8_t CLV(const instr_param_t *param);
    uint8_t CMP(const instr_param_t *param);
    uint8_t CPX(const instr_param_t *param);
    uint8_t CPY(const instr_param_t *param);

    uint8_t DEC(const instr_param_t *param);
    uint8_t DEX(const instr_param_t *param);
    uint8_t DEY(const instr_param_t *param);

    uint8_t EOR(const instr_param_t *param);

    uint8_t INC(const instr_param_t *param);
    uint8_t INX(const instr_param_t *param);
    uint8_t INY(const instr_param_t *param);

    uint8_t JMP(const instr_param_t *param);
    uint8_t JSR(const instr_param_t *param);

    uint8_t LDA(const instr_param_t *param);
    uint8_t LDX(const instr_param_t *param);
    uint8_t LDY(const instr_param_t *param);
    uint8_t LSR(const instr_param_t *param);

    uint8_t NOP(const instr_param_t *param);

    uint8_t ORA(const instr_param_t *param);

    uint8_t PHA(const instr_param_t *param);
    uint8_t PHP(const instr_param_t *param);
    uint8_t PLA(const instr_param_t *param);
    uint8_t PLP(const instr_param_t *param);

    uint8_t ROL(const instr_param_t *param);
    uint8_t ROR(const instr_param_t *param);
    uint8_t RTI(const instr_param_t *param);
    uint8_t RTS(const instr_param_t *param);

    uint8_t SBC(const instr_param_t *param);
    uint8_t SEC(const instr_param_t *param);
    uint8_t SED(const instr_param_t *param);
    uint8_t SEI(const instr_param_t *param);
    uint8_t STA(const instr_param_t *param);
    uint8_t STX(const instr_param_t *param);
    uint8_t STY(const instr_param_t *param);

    uint8_t TAX(const instr_param_t *param);
    uint8_t TAY(const instr_param_t *param);
    uint8_t TSX(const instr_param_t *param);
    uint8_t TXA(const instr_param_t *param);
    uint8_t TXS(const instr_param_t *param);
    uint8_t TYA(const instr_param_t *param);

#endif // _NES_CPU_
