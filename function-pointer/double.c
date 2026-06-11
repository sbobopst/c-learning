#include <stdio.h>

void raddoppia(int *n){
    *n = *n * 2;
}

int main(){
    int x = 10;
    raddoppia(&x);
    printf("Valore raddoppiato di x: %d\n", x);
    return 0;
}