#include <stddef.h>
#include <stdint.h>
#if !defined(_NES_CPU_)
#define _NES_CPU_

    // Includes
    #include "hdefault.h"
    #include "ram.h"
    
    // Constants
    #define b_true = -1; // Just to set true at 1 bit fields
    #define b_false = 0; // Just to set false at 1 bit fields
    #define STACK_START 0x01FF
    #define STACK_END 0x0100
    
    // Errors
    #define ERR_CPU_NOT_LOADED -100

    // Address Modes
    typedef enum ADDRESS_MODE{
        accumulator,
        immediate,
        implied,
        relative,
        indirect,
        indirect_x,
        indirect_y,
        absolute,
        absolute_x,
        absolute_y,
        zero_page,
        zero_page_x,
        zero_page_y,
        qtd_addr
    } addr_mode_t;

    typedef enum OPERATION{
        LDA, LDX, LDY, STA, STX, STY, TAX, TAY, TXA,
        TYA, TSX, TXS, PHA, PHP, PLA, PLP, AND, EOR,
        ORA, BIT, ADC, SBC, CMP, CPX, CPY, INC, INX,
        INY, DEC, DEX, DEY, ASL, LSR, ROL, ROR, JMP,
        JSR, RTS, BCC, BCS, BEQ, BMI, BNE, BPL, BVC,
        BVS, CLC, CLD, CLI, CLV, SEC, SED, SEI, BRK,
        NOP, RTI, qtd_op
    } operation_t;

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

    typedef struct{
        operation_t op;
        size_t size;
        uint8_t cycles;
        addr_mode_t addr_mode;
    } cpuinst_t;

    /**
     * Structure to emulate a nes cpu
     *
     *  @param `uint8_t cycles`: Stores the remaining cycles to finish the instruction
     *  @param `uint8_t ACC`: Accumulator
     *  @param `uint8_t X`: Index Register X
     *  @param `uint8_t Y`: Index Register Y
     *  @param `uint8_t STK`: Stack pointer
     *  @param `status_t STATUS`: Status Reg
     *  @param `uint16_t PC`: Program Counter
     *  @param `cpuinst_t instr[0xFF]`: Set of cpu valid instructions */
    typedef struct R6502{
        uint8_t cycles;

        //* Registers
        uint8_t ACC; // Accumulator
        uint8_t X; // Index Register X
        uint8_t Y; // Index Register Y
        uint8_t STK; // Stack pointer
        status_t STATUS; // Status Reg
        uint16_t PC; // Program Counter

        cpuinst_t instr[0xFF]; // Set of instructions
    } R6502_t;

    /**
     * Start CPU structure to emulate NES R6502 cpu
     * @param `R6502_t *cpu`: cpu to get default loaded 
     *
     * @Return if the operation was sucessifull */
    int cpu_start(R6502_t *cpu);
    void cpu_print(R6502_t proc);
    int cpu_load_instr(R6502_t *cpu);
    uint8_t fetch(R6502_t *cpu);
    int exec(R6502_t *cpu, uint8_t op_code);

    // Default param structure
    typedef struct {
        R6502_t *cpu;
        uint16_t data;
        bool is_memory;
        bool *additional_cycle;
    } op_param_t;

    typedef struct {
        R6502_t *cpu;
        uint16_t *data;
        bool *additional_cycle;
    } addr_param_t;

    // ----------- operations -----------
    // Load/Store
    void op_LDA(op_param_t param);
    void op_LDX(op_param_t param);
    void op_LDY(op_param_t param);
    void op_STA(op_param_t param);
    void op_STX(op_param_t param);
    void op_STY(op_param_t param);

    // Registers Transfer
    void op_TAX(op_param_t param);
    void op_TAY(op_param_t param);
    void op_TXA(op_param_t param);
    void op_TYA(op_param_t param);

    // Stack
    void op_TSX(op_param_t param);
    void op_TXS(op_param_t param);
    void op_PHA(op_param_t param);
    void op_PHP(op_param_t param);
    void op_PLA(op_param_t param);
    void op_PLP(op_param_t param);

    // Logical
    void op_AND(op_param_t param);
    void op_EOR(op_param_t param);
    void op_ORA(op_param_t param);
    void op_BIT(op_param_t param);

    // Arithmetic
    void op_ADC(op_param_t param);
    void op_SBC(op_param_t param);
    void op_CMP(op_param_t param);
    void op_CPX(op_param_t param);
    void op_CPY(op_param_t param);

    // Increment/Decrement
    void op_INC(op_param_t param);
    void op_INX(op_param_t param);
    void op_INY(op_param_t param);
    void op_DEC(op_param_t param);
    void op_DEX(op_param_t param);
    void op_DEY(op_param_t param);

    // Shift
    void op_ASL(op_param_t param);
    void op_LSR(op_param_t param);
    void op_ROL(op_param_t param);
    void op_ROR(op_param_t param);

    // Jump
    void op_JMP(op_param_t param);
    void op_JSR(op_param_t param);
    void op_RTS(op_param_t param);

    // Branch
    void op_BCC(op_param_t param);
    void op_BCS(op_param_t param);
    void op_BEQ(op_param_t param);
    void op_BMI(op_param_t param);
    void op_BNE(op_param_t param);
    void op_BPL(op_param_t param);
    void op_BVC(op_param_t param);
    void op_BVS(op_param_t param);

    // Status Flag
    void op_CLC(op_param_t param);
    void op_CLD(op_param_t param);
    void op_CLI(op_param_t param);
    void op_CLV(op_param_t param);
    void op_SEC(op_param_t param);
    void op_SED(op_param_t param);
    void op_SEI(op_param_t param);
    
    // System
    void op_BRK(op_param_t param);
    void op_NOP(op_param_t param);
    void op_RTI(op_param_t param);

    // ----------- address modes -----------
    void addr_immediate(addr_param_t param);
    void addr_accumulator(addr_param_t param);
    void addr_implied(addr_param_t param);
    void addr_relative(addr_param_t param);
    void addr_indirect(addr_param_t param);
    void addr_indirect_x(addr_param_t param);
    void addr_indirect_y(addr_param_t param);
    void addr_absolute(addr_param_t param);
    void addr_absolute_x(addr_param_t param);
    void addr_absolute_y(addr_param_t param);
    void addr_zero_page(addr_param_t param);
    void addr_zero_page_x(addr_param_t param);
    void addr_zero_page_y(addr_param_t param);

    int load_op_tbl();
    int load_addr_tbl();

    extern void (*op_tbl[qtd_op])(op_param_t);
    extern void (*addr_tbl[qtd_addr])(addr_param_t);

#endif // _NES_CPU_
