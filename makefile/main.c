#include "gpio.h"
#include <stdio.h> //E' presente su gpio.c, NON gpio.h

int main(void) {
    uint8_t reg = 0;
    print_reg(reg);

    set_bit(&reg, 3);
    print_reg(reg);

    set_bit(&reg, 5);
    print_reg(reg);

    clear_bit(&reg, 3);
    print_reg(reg);

    printf("Make eseguito!\n");
    return 0;
}