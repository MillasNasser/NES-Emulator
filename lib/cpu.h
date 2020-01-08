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
        C = (1 << 0),
        Z = (1 << 1),
        I = (1 << 2),
        D = (1 << 3),
        B = (1 << 4),
        U = (1 << 5),
        V = (1 << 6),
        N = (1 << 7),
    };

    typedef struct {
        char name[4];
        uint8_t (*op)();
        uint8_t (*addr_mode);
        uint8_t cycles;
    } instruction_t;
    

    typedef struct {
        struct bus_t *bus;

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

    // uint8_t cpu_read(R6502 *cpu, uint16_t addr);
    // void cpu_write(R6502 *cpu, uint16_t addr, uint8_t data);

    //? Signals
    void clock();
    void RDY();
    void IRQ();
    void NMI();
    void SO();
    void RES();

    //? Addressing modes
    uint8_t Accum();
    uint8_t IMM();
    uint8_t Abs();
    uint8_t ZP();
    uint8_t ZPX();
    uint8_t ZPY();
    uint8_t ABSX();
    uint8_t ABSY();
    uint8_t Implied();
    uint8_t Relative();
    uint8_t INDX();
    uint8_t INDY();
    uint8_t IND();

    //? Intructions
    uint8_t ADC();
    uint8_t AND();
    uint8_t ASL();

    uint8_t BCC();
    uint8_t BCS();
    uint8_t BEQ();
    uint8_t BIT();
    uint8_t BMI();
    uint8_t BNE();
    uint8_t BPL();
    uint8_t BRK();
    uint8_t BVC();
    uint8_t BVS();

    uint8_t CLC();
    uint8_t CLD();
    uint8_t CLI();
    uint8_t CLV();
    uint8_t CMP();
    uint8_t CPX();
    uint8_t CPY();

    uint8_t DEC();
    uint8_t DEX();
    uint8_t DEY();

    uint8_t EOR();

    uint8_t INC();
    uint8_t INX();
    uint8_t INY();

    uint8_t JMP();
    uint8_t JSR();

    uint8_t LDA();
    uint8_t LDX();
    uint8_t LDY();
    uint8_t LSR();

    uint8_t NOP();

    uint8_t ORA();

    uint8_t PHA();
    uint8_t PHP();
    uint8_t PLA();
    uint8_t PLP();

    uint8_t ROL();
    uint8_t ROR();
    uint8_t RTI();
    uint8_t RTS();

    uint8_t SBC();
    uint8_t SEC();
    uint8_t SED();
    uint8_t SEI();
    uint8_t STA();
    uint8_t STX();
    uint8_t STY();

    uint8_t TAX();
    uint8_t TAY();
    uint8_t TSX();
    uint8_t TXA();
    uint8_t TXS();
    uint8_t TYA();
    
#endif // _NES_CPU_