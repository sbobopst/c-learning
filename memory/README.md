# Stack vs Heap

Una variabile normale, come `int n` in `main`, vive sullo **stack**: memoria automatica, gestita dal compilatore, che viene creata e liberata da sola in base alle funzioni che vengono chiamate e che terminano.

```c
int n = 0;   // stack — esiste finché main() è in esecuzione, poi sparisce da sola
```

L'array creato con `malloc` invece vive sull'**heap**: memoria che il programmatore deve gestire esplicitamente, chiedendola con `malloc` e restituendola con `free`. Niente avviene automaticamente.

```
Stack:                          Heap:
┌──────────────────┐           ┌──────────────────────────┐
│ n (int)           │           │ arr → array di interi     │
│ creata e liberata  │           │ richiesto con malloc,      │
│ automaticamente    │           │ resta finché non si fa     │
│                    │           │ free() esplicitamente      │
└──────────────────┘           └──────────────────────────┘
```

In questo progetto, `n` (la dimensione dell'array) sta sullo stack — esiste e basta, nessuna gestione richiesta. L'array a cui punta `arr`, invece, sta sull'heap — esiste solo perché è stato esplicitamente allocato con `malloc`, e resterà occupato finché non viene esplicitamente rilasciato con `free`.

L'heap serve qui perché la dimensione dell'array non è nota a compile-time — dipende da un input letto a runtime. Un array sullo stack, come quelli usati nei livelli precedenti, deve invece avere una dimensione fissa, nota già quando il programma viene compilato.

## `malloc` — allocazione e controllo

```c
int *arr = malloc(*n * sizeof(int));
if (arr == NULL) {
    printf("Errore\n");
    return NULL;
}
```

`malloc` chiede al sistema `*n * sizeof(int)` byte sull'heap. Può fallire (memoria esaurita) e in quel caso restituisce `NULL` — va controllato **sempre**, prima di usare il puntatore restituito.

L'ordine conta: la validazione di `*n <= 0` avviene **prima** della chiamata a `malloc`, non dopo. Allocare con una dimensione negativa o zero produce un comportamento poco prevedibile (la moltiplicazione tra un intero negativo e `sizeof`, che è `unsigned`, dà un risultato enorme e sbagliato).

---

## Propagazione dell'errore tra funzioni — `NULL` come segnale

`crea_array` può fallire e restituire `NULL`.

```c
if (*n <= 0)     { ...; return NULL; }   // input non valido
```

Chi chiama la funzione (`main`) ha la responsabilità di controllare questo valore di ritorno **prima** di usare il puntatore:

```c
int *arr = crea_array(&n);
if (arr == NULL) {
    return -1;   // crea_array ha già stampato il motivo dell'errore
}
```

Senza questo controllo, se `crea_array` fallisse, `arr` sarebbe `NULL` e la riga successiva (`riempi_array`, che scrive su `arr[i]`) causerebbe un crash — tentativo di scrittura su un indirizzo nullo.

---

## `free` e pulizia finale

```c
free(arr);
arr = NULL;
```

La memoria allocata da `malloc` dentro `crea_array` viene rilasciata in `main`, una volta che non serve più — dopo aver stampato somma e media. Ogni `malloc` deve avere un `free` corrispondente, altrimenti quella memoria resta occupata per tutta la vita del programma (memory leak).

Assegnare `arr = NULL` subito dopo `free` è una pratica di sicurezza: `free` non modifica il valore del puntatore, che continuerebbe a contenere lo stesso indirizzo ormai non più valido (dangling pointer). Azzerarlo esplicitamente rende impossibile un accesso accidentale a quella memoria più avanti nel codice.

---

## Codice completo
[memory-pt2.c](./memory-pt2.c)  
[arr.c](./arr.c)