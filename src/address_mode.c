#include "cpu.h"
#include "ram.h"
#include <stdbool.h>
#include <stdint.h>


void addr_immediate(addr_param_t param) {
    uint8_t data = fetch();
    param.cpu->PC++;

    *param.data = data;
    *param.additional_cycle = false;
}

void addr_accumulator(addr_param_t param) {
    *param.additional_cycle = false;
}

void addr_implied(addr_param_t param) {
    addr_accumulator(param);
}

void addr_relative(addr_param_t param) {
    not_imp();
}

void addr_indirect(addr_param_t param) {
    not_imp();
}

void addr_indirect_x(addr_param_t param) {
    not_imp();
}

void addr_indirect_y(addr_param_t param) {
    not_imp();
}

void addr_absolute(addr_param_t param) {
    uint16_t lo = fetch(); param.cpu->PC++;
    uint16_t hi = fetch(); param.cpu->PC++;

    *param.data = (hi<<8) | lo;
    *param.additional_cycle = false;
}

void addr_absolute_x(addr_param_t param) {
    bool req_cycle = false;
    uint16_t lo = fetch(); param.cpu->PC++;
    uint16_t hi = fetch(); param.cpu->PC++;

    *param.data = (hi<<8) | lo;
    *param.data += param.cpu->X;

    if ( hi != (*param.data >> 8) ) req_cycle = true;
    
    *param.additional_cycle = req_cycle;
}

void addr_absolute_y(addr_param_t param) {
    bool req_cycle = false;
    uint16_t lo = fetch(); param.cpu->PC++;
    uint16_t hi = fetch(); param.cpu->PC++;

    *param.data = (hi<<8) | lo;
    *param.data += param.cpu->Y;

    if ( hi != (*param.data >> 8) ) req_cycle = true;
    
    *param.additional_cycle = req_cycle;
}

void addr_zero_page(addr_param_t param) {
    not_imp();
}

void addr_zero_page_x(addr_param_t param) {
    uint8_t data = fetch();

    param.data = ram_read(data + param.cpu->X) & 0x00ff;
}

void addr_zero_page_y(addr_param_t param) {
    not_imp();
}

void (*addr_tbl[qtd_addr])(addr_param_t) = {0};
int load_addr_tbl(){
    addr_tbl[accumulator] = addr_accumulator;
    addr_tbl[immediate] = addr_immediate;
    addr_tbl[implied] = addr_implied;
    addr_tbl[relative] = addr_relative;
    addr_tbl[indirect] = addr_indirect;
    addr_tbl[indirect_x] = addr_indirect_x;
    addr_tbl[indirect_y] = addr_indirect_y;
    addr_tbl[absolute] = addr_absolute;
    addr_tbl[absolute_x] = addr_absolute_x;
    addr_tbl[absolute_y] = addr_absolute_y;
    addr_tbl[zero_page] = addr_zero_page;
    addr_tbl[zero_page_x] = addr_zero_page_x;
    addr_tbl[zero_page_y] = addr_zero_page_y;

    return 0;
}
