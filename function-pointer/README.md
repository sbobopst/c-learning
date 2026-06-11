
## Passaggio per valore vs passaggio per riferimento

### Il problema

In C, quando passi una variabile a una funzione, viene passata una **copia**. La funzione non sa dove vive la variabile originale e non può modificarla.

```c
void raddoppia(int n) {
    n = n * 2;   // modifica solo la copia locale
}

int main(void) {
    int x = 10;
    raddoppia(x);
    printf("%d\n", x);   // stampa 10 — x non è cambiato
    return 0;
}
```

Quello che succede in memoria:

```
main chiama raddoppia(x):

main:       x = 10   (indirizzo es. 0x100)
raddoppia:  n = 10   (indirizzo es. 0x200)  ← COPIA di x

raddoppia:  n = 20   ← modifica solo la copia

raddoppia ritorna:
main:       x = 10   ← invariato
            n        ← non esiste più, stack liberato
```

### La soluzione — passaggio per riferimento

Per modificare `x` dall'interno della funzione, si passa **l'indirizzo di x**. La funzione riceve un puntatore e modifica ciò che sta a quell'indirizzo.

### Codice

[double.c](./double.c)

```
main chiama raddoppia(&x):

raddoppia:  n = 0x100     ← l'INDIRIZZO di x, non una copia
            *n = *n * 2   ← va a 0x100 e modifica il valore lì
main:       x = 20        ← modificato!
```

## Swap — scambio di due variabili

### Concetti coperti

- Passaggio per riferimento con due puntatori
- Variabile temporanea per lo scambio
- Convenzione di naming (`swap` è una funzione standard in molte librerie)

### Codice

[swap.c](./swap.c)

### Perché serve la variabile temporanea

Senza `tmp` il valore originale di `*a` viene sovrascritto prima di essere salvato:

```c
// SBAGLIATO — perde il valore originale di *a
*a = *b;
*b = *a;   // ora *a vale già *b → entrambi uguali

// CORRETTO — salva prima
int tmp = *a;
*a = *b;
*b = tmp;
```

## Array e aritmetica dei puntatori

### Concetti coperti

- Un array è già un puntatore al primo elemento
- Aritmetica dei puntatori — `arr+i` scala per `sizeof(tipo)`
- `sizeof(arr) / sizeof(int)` per calcolare la lunghezza
- `size_t` per indici e dimensioni

### Array = puntatore al primo elemento

```c
int arr[5] = {10, 20, 30, 40, 50};

arr        // indirizzo del primo elemento → uguale a &arr[0]
*arr       // valore del primo elemento   → uguale a arr[0]
*(arr+2)   // valore del terzo elemento   → uguale a arr[2]
```

Verifica empirica:

```
arr      = 0x7ffe964ce160   ← indirizzo primo elemento
&arr[0]  = 0x7ffe964ce160   ← identico
&arr[2]  = 0x7ffe964ce168   ← +8 byte (2 elementi × 4 byte)
arr+2    = 0x7ffe964ce168   ← identico
```

### Aritmetica dei puntatori

`arr + n` non significa "indirizzo + n byte" — significa "indirizzo + n elementi":

```
arr + 1  →  indirizzo + (1 × sizeof(int))  →  +4 byte
arr + 2  →  indirizzo + (2 × sizeof(int))  →  +8 byte
```

Il compilatore conosce il tipo e scala automaticamente. Su firmware cambia in base al tipo:

| Tipo | sizeof | arr+1 sposta di |
|---|---|---|
| `uint8_t` | 1 byte | +1 byte |
| `uint16_t` | 2 byte | +2 byte |
| `uint32_t` | 4 byte | +4 byte |
| `int` (PC 64-bit) | 4 byte | +4 byte |
| puntatore (PC 64-bit) | 8 byte | +8 byte |

### Calcolo della lunghezza con sizeof

```c
size_t len = sizeof(arr) / sizeof(int);
// sizeof(arr) = 5 × 4 = 20 byte
// sizeof(int) = 4 byte
// len = 5
```

Vantaggio: se aggiungi elementi all'array il calcolo si aggiorna automaticamente. Mai hardcodare la lunghezza.

`size_t` è il tipo corretto per dimensioni e indici — senza segno, dimensione dipendente dall'architettura. Lo troverai ovunque nelle funzioni standard (`memcpy`, `memset`, `strlen`).

### Codice

[array.c](./array.c)

## Somma di array con puntatori

### Concetti coperti

- Funzione che riceve un array come puntatore
- Perché si passa `arr` senza `&`
- Uso di aritmetica dei puntatori invece di `[]`

### Codice

[arrayptr-sum.c](./arrayptr-sum.c)

### Perché si passa `arr` senza `&`

```c
arraySum(arr, len)    // arr è già un indirizzo → int *arr lo riceve direttamente
arraySum(&arr, len)   // sarebbe int ** → indirizzo dell'indirizzo, tipo sbagliato
```

`arr` da solo è già l'indirizzo del primo elemento — esattamente quello che si vuole passare. Aggiungere `&` creerebbe un doppio livello di indirezione.
