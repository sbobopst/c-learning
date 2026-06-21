#include "arr.h"

int* crea_array(int *n){
    printf("Inserire dimensione array: ");
    scanf("%d", n);
    
    if (*n <= 0) {
        printf("Errore: dimensione non valida\n");
        return NULL;
    }
    
    int *arr = malloc(*n * sizeof(int));
    return arr;
}

void riempi_array(int *arr, int n){
    for (int i=0; i<n; i++){
        printf("Inserire %d° elemento: ", i+1);
        scanf("%d", &arr[i]);
    }
}

void stampa_array(int *arr, int n){
    for (int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int somma_array(int *arr, int n){
    int sum = 0;
    for (int i=0; i<n; i++){
        sum += arr[i];
    }
    return sum;
}
