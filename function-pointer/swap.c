#include <stdio.h>

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(){
    int a = 10;
    int b = 20;
    printf("PRE SWAP ---\n Valore di a: %d\n Valore di b: %d\n", a,b);
    swap(&a, &b);
    printf("POST SWAP ---\n Valore di a: %d\n Valore di b: %d\n", a,b);
}