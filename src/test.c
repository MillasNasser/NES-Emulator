#include "test.h"

/**
 * Function to test all addressing modes
 * 
 * - [x] immediate
 * - [ ] accumulator
 * - [ ] implied
 * - [ ] relative
 * - [ ] indirect
 * - [x] indirect_x
 * - [x] indirect_y
 * - [x] indirect_y (Page Boundary)
 * - [x] absolute
 * - [x] absolute_x
 * - [x] absolute_x (Page Boundary)
 * - [x] absolute_y
 * - [x] absolute_y (Page Boundary)
 * - [x] zero_page
 * - [x] zero_page_x
 * - [ ] zero_page_y
 *
 * @param R6502_t cpu: cpu to execute all addressing modes
 * @Return there's no value returned
*/
void test_addr_mode(R6502_t cpu) {
    uint8_t contador = 0;
    #define inst_id contador++

    // Testes no processo
    printf("Testing Immediate address\n");
    // 0x69 | ADC | cycles=2| immediate
    ram_write(inst_id, 0x69); // op_code
    ram_write(inst_id, 69); // immediate
    
    exec(&cpu, fetch(&cpu));
    cpu_print(cpu);

    printf("Testing absolute address\n");
    // 0x6D | ADC | cycles=4| absolute
    ram_write(0x0420, 69); // Adding data to RAM
    ram_write(inst_id, 0x6D); // op_code
    ram_write(inst_id, 0x20); // addr lo
    ram_write(inst_id, 0x04); // addr hi

    exec(&cpu, fetch(&cpu));
    cpu_print(cpu);

    printf("Testing absolute address indexed by X\n");
    // 0x7D | ADC | cycles=4| absolute_x
    cpu.X = 0xA; // index 10 in decimal mode
    ram_write(0x6969, 1); // Adding data to RAM
    ram_write(inst_id, 0x7D); // op_code
    ram_write(inst_id, 0x5F); // addr lo
    ram_write(inst_id, 0x69); // addr hi

    exec(&cpu, fetch(&cpu));
    cpu_print(cpu);

    printf("Testing absolute address indexed by X (Page Boundary)\n");
    // 0x7D | ADC | cycles=4| absolute_x
    cpu.X = 0xA; // index 10 in decimal mode
    ram_write(0x6909, 2); // Adding data to RAM
    ram_write(inst_id, 0x7D); // op_code
    ram_write(inst_id, 0xFF); // addr lo
    ram_write(inst_id, 0x68); // addr hi

    exec(&cpu, fetch(&cpu));
    cpu_print(cpu);

    printf("Testing absolute address indexed by Y\n");
    // 0x79 | ADC | cycles=4| absolute_y
    cpu.Y = 0x42; // index 10 in decimal mode
    ram_write(0x4242, 2); // Adding data to RAM
    ram_write(inst_id, 0x79); // op_code
    ram_write(inst_id, 0x00); // addr lo
    ram_write(inst_id, 0x42); // addr hi

    exec(&cpu, fetch(&cpu));
    cpu_print(cpu);

    printf("Testing absolute address indexed by Y (Page Boundary)\n");
    // 0x79 | ADC | cycles=4| absolute_y
    cpu.Y = 0x43; // index 10 in decimal mode
    ram_write(0x4242, 2); // Adding data to RAM
    ram_write(inst_id, 0x79); // op_code
    ram_write(inst_id, 0xFF); // addr lo
    ram_write(inst_id, 0x41); // addr hi

    exec(&cpu, fetch(&cpu));
    cpu_print(cpu);

    printf("Testing zero page address\n");
    // 0x65 | ADC | cycles=3| zero_page
    ram_write(0xFF, 1); // Adding data to RAM
    ram_write(inst_id, 0x65); // op_code
    ram_write(inst_id, 0xFF); // addr lo

    exec(&cpu, fetch(&cpu));
    cpu_print(cpu);

    printf("Testing zero page address indexed by X\n");
    // 0x75 | ADC | cycles=4| zero_page_x
    cpu.X = 0x5; // index 10 in decimal mode
    ram_write(0xFF, 2); // Adding data to RAM
    ram_write(inst_id, 0x75); // op_code
    ram_write(inst_id, 0xFA); // addr lo

    exec(&cpu, fetch(&cpu));
    cpu_print(cpu);

    printf("Testing indexed x address\n");
    // 0x61 | ADC | cycles=6| indirect_x
    cpu.X = 0xF; // index 10 in decimal mode
    ram_write(0x7070, -3); // Adding data to RAM
    ram_write(0x69, 0x70); // Adding data to RAM
    ram_write(0x6A, 0x70); // Adding data to RAM
    ram_write(inst_id, 0x61); // op_code
    ram_write(inst_id, 0x5A); // addr lo

    exec(&cpu, fetch(&cpu));
    cpu_print(cpu);

    printf("Testing indexed y address\n");
    // 0x71 | ADC | cycles=5| indirect_y
    cpu.Y = 0xA; // index 10 in decimal mode
    ram_write(0xAFFF, 10); // Adding data to RAM
    ram_write(0x40, 0xF5); // Adding data to RAM
    ram_write(0x41, 0xAF); // Adding data to RAM
    ram_write(inst_id, 0x71); // op_code
    ram_write(inst_id, 0x40); // addr lo

    exec(&cpu, fetch(&cpu));
    cpu_print(cpu);

    printf("Testing indexed y address (Page Boundary)\n");
    // 0x71 | ADC | cycles=5| indirect_y
    cpu.Y = 0xFF; // index 10 in decimal mode
    ram_write(0xAFFE, 100); // Adding data to RAM
    ram_write(0x40, 0xFF); // Adding data to RAM
    ram_write(0x41, 0xAE); // Adding data to RAM
    ram_write(inst_id, 0x71); // op_code
    ram_write(inst_id, 0x40); // addr lo

    exec(&cpu, fetch(&cpu));
    cpu_print(cpu);
}

