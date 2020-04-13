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

    typedef union {
        struct {
            char C_CARRY:1;
            char Z_ZERO:1;
            char I_IRQ_DISABLE:1;
            char D_DECIMAL:1;
            char B_BRK:1;
            char U_UNABLE:1;
            char V_OVERFLOW:1;
            char N_NEGATIVE:1;
        };

        uint8_t status;
    } status_t;


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
        status_t STATUS; // Status Reg
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
    #define instr_params R6502 *cpu

    uint8_t ADC(instr_params);
    uint8_t AND(instr_params);
    uint8_t ASL(instr_params);

    uint8_t BCC(instr_params);
    uint8_t BCS(instr_params);
    uint8_t BEQ(instr_params);
    uint8_t BIT(instr_params);
    uint8_t BMI(instr_params);
    uint8_t BNE(instr_params);
    uint8_t BPL(instr_params);
    uint8_t BRK(instr_params);
    uint8_t BVC(instr_params);
    uint8_t BVS(instr_params);

    uint8_t CLC(instr_params);
    uint8_t CLD(instr_params);
    uint8_t CLI(instr_params);
    uint8_t CLV(instr_params);
    uint8_t CMP(instr_params);
    uint8_t CPX(instr_params);
    uint8_t CPY(instr_params);

    uint8_t DEC(instr_params);
    uint8_t DEX(instr_params);
    uint8_t DEY(instr_params);

    uint8_t EOR(instr_params);

    uint8_t INC(instr_params);
    uint8_t INX(instr_params);
    uint8_t INY(instr_params);

    uint8_t JMP(instr_params);
    uint8_t JSR(instr_params);

    uint8_t LDA(instr_params);
    uint8_t LDX(instr_params);
    uint8_t LDY(instr_params);
    uint8_t LSR(instr_params);

    uint8_t NOP(instr_params);

    uint8_t ORA(instr_params);

    uint8_t PHA(instr_params);
    uint8_t PHP(instr_params);
    uint8_t PLA(instr_params);
    uint8_t PLP(instr_params);

    uint8_t ROL(instr_params);
    uint8_t ROR(instr_params);
    uint8_t RTI(instr_params);
    uint8_t RTS(instr_params);

    uint8_t SBC(instr_params);
    uint8_t SEC(instr_params);
    uint8_t SED(instr_params);
    uint8_t SEI(instr_params);
    uint8_t STA(instr_params);
    uint8_t STX(instr_params);
    uint8_t STY(instr_params);

    uint8_t TAX(instr_params);
    uint8_t TAY(instr_params);
    uint8_t TSX(instr_params);
    uint8_t TXA(instr_params);
    uint8_t TXS(instr_params);
    uint8_t TYA(instr_params);

    //? Instruction table
    typedef struct {
        const char name[8];
        uint8_t (*op)();
        uint8_t (*addr_mode)();
        uint8_t cycles;
    } instruction_t;
    #define NO_INSTR ((instruction_t){"???", NULL, NULL, 0})

    instruction_t cpu_instr_tbl[256];

#endif // _NES_CPU_
