#include <stdio.h>
#include "gpio.h"
void print_reg(uint8_t reg){
    printf("0b: ");
    for(int i=7; i>=0; i--){
        printf("%d", (reg>>i)&1);
    }
    printf("\n");
}

//USO ptr *reg ALTRIMENTI NON MODIFICO effettivamente reg presente nel main.c ma bensi la sua copia
void set_bit(uint8_t *reg, int n) {
    *reg |= (1U << n);
}

void clear_bit(uint8_t *reg, int n) {
    *reg &= ~(1U << n);
}

void toggle_bit(uint8_t *reg, int n) {
    *reg ^= (1U << n);
}

int read_bit(uint8_t reg, int n) {
    return (reg >> n) & 1;
}