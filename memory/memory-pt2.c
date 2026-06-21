/* TEST COMPLETO CON SUDDIVISIONE DI HEADER E SOURCE E USO DI MAKEFILE */

#include "arr.h"

int main(){
   int n = 0;
   int *arr = crea_array(&n);
   if (arr == NULL) {
       return -1;   
   }
   riempi_array(arr,n);
   stampa_array(arr, n);

   int sum = somma_array(arr, n);
   printf("La somma dell'array è: %d\n", sum);
   printf("La media è: %.2f\n", (double)sum / n);

   free(arr);
   arr = NULL;

   return 0;
}