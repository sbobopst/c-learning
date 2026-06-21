#include <stdio.h>
#include <stdlib.h>

int main(){
    int n = 0;
    printf("Inserire dimensione array: ");
    scanf("%d", &n);
    
    if (n <= 0) {
        printf("Errore: dimensione non valida\n");
        return -1;
    }

    int *arr = malloc(n * sizeof(int));

    if(arr==NULL){
        printf("Errore\n");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = i * 10;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
    printf("%p\n", arr);   // indirizzo ancora "valido" come numero, malloc non lo cambia

    free(arr);

    /* ESPERIMENTO VOLUTO — dangling pointer:
       arr punta a memoria già liberata. Il contenuto che leggiamo qui
       è undefined behavior: può essere spazzatura, i vecchi valori per
       puro caso, o causare un crash. NON va mai fatto in codice reale,
       tenuto qui solo per osservare il comportamento. */
       
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    arr=NULL;   // arr non punta più a memoria valida — pratica corretta dopo free
    printf("%p\n", arr);

    return 0; 
}