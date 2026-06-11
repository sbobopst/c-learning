#include <stdio.h>

int main(){
    int arr[5] = {10,20,30,40,50};
    printf("VALORI\narr[0] = %d\n", arr[0]);
    printf("*arr = %d\n", *arr);
    printf("arr[2] = %d\n", arr[2]);
    printf("*(arr+2) = %d\n", *(arr+2));

    printf("PUNTATORI\n&arr[0] = %p\n", &arr[0]);
    printf("arr = %p\n", arr);
    printf("&arr[2] = %p\n", &arr[2]);
    printf("arr+2 = %p\n", arr+2);

    return 0;
}