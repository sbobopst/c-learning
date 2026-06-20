#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

void print_reg(uint8_t);
void set_bit(uint8_t *reg, int n);
void clear_bit(uint8_t *reg, int n);
void toggle_bit(uint8_t *reg, int n);
int  read_bit(uint8_t reg, int n);

#endif