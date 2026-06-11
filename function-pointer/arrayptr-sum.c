#include <stdio.h>

int arraySum(int *arr, size_t len){
    int sum=0;
    for(int i=0; i<len; i++){
        sum += *(arr+i);    
    }
    return sum;
}

int main(){
    int arr[5] = {12,24,31,49,53};
    size_t len = sizeof(arr) / sizeof(int);
    printf("%d\n", arraySum(arr, len));
}