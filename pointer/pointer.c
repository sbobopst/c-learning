#include <stdio.h>

int main(){
    int x = 42;
    int *p = &x;
    
    printf("Valore di x: %d\n", x);
    printf("Indirizzo di x: %p\n", &x);
    printf("Valore di p: %p\n", p);
    printf("Indirizzo di p: %p\n", &p);
    printf("Valore puntato da p: %d\n", *p);
    
    *p = 100;
    printf("Valore di x post modifica tramite p: %d\n", x);
    
    int **pp = &p;
    printf("Catena di pointer pp (valore di x): %d\n", **pp);
}