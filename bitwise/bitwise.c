#include <stdint.h> //utilizzato per dichiarare uint8_t
#include <stdio.h>

void print_reg(uint8_t reg){
    printf("reg 0b: ");
    for (int i=7; i>=0 ; i--){
        printf("%d", (reg>>i) & 1);
    }
    printf("\n");
}

int main(){
    uint8_t reg = 0;
    print_reg(reg);

    printf("OR:\n");
    //accensione pin 3 e 5 (OR)
    reg |= (1U<<3);
    print_reg(reg);
    reg |= (1U<<5);
    print_reg(reg);

    printf("AND:\n");
    //spegnimento pin 3 e 5 (AND)
    reg &= ~(1U<<3);
    print_reg(reg);
    reg &= ~(1U<<5);
    print_reg(reg);

    printf("XOR:\n");
    //se acceso => spegni, se spento => accendi (XOR) 
    reg ^= (1U << 3);   
    print_reg(reg);
    reg |= (1U<<3);
    reg ^= (1U << 3);
    print_reg(reg);
}


