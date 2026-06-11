## Livello 2 — Puntatori

### Concetti coperti

- Indirizzi di memoria e operatore `&`
- Dichiarazione e dereferenziazione di puntatori (`*`)
- Puntatori a puntatori (`**`)
- Come la RAM è organizzata (modello a "case numerate")

### Il modello mentale

La RAM è come una strada con case numerate. Ogni variabile occupa una o più case:

```
Indirizzo:  100    101    102    103    104
           ┌─────┬─────┬─────┬─────┬─────┐
Contenuto: │  0  │  0  │ 42  │  0  │  0  │
           └─────┴─────┴─────┴─────┴─────┘
                         ▲
                    int x = 42
```

Un **puntatore** è una variabile che contiene un indirizzo — il numero della casa, non il contenuto.

### Codice finale — puntatori base

[pointer.c](./pointer.c)

### La catena di indirezione

```
pp  →  indirizzo di p
*pp →  p  →  indirizzo di x
**pp → x  →  42
```

| Dichiarazione | Inizializzazione corretta | Perché |
|---|---|---|
| `int *p` | `&x` | p deve contenere l'indirizzo di un `int` |
| `int **pp` | `&p` | pp deve contenere l'indirizzo di un `int *` |

### Dimensione dei puntatori

| Architettura | Dimensione puntatore |
|---|---|
| PC 64-bit (Ubuntu) | 8 byte |
| STM32 32-bit | 4 byte |

Per questo `&x` e `&p` differiscono di 8 byte su PC — ogni variabile occupa il suo spazio in memoria e i puntatori hanno dimensione fissa dipendente dall'architettura.

### Collegamento al firmware

Sul firmware i puntatori sono usati direttamente per accedere ai registri hardware:

```c
// Accendere un LED su STM32 scrivendo direttamente al registro GPIO
*((uint32_t*)0x48000018) = 1;
// ↑ stai scrivendo il valore 1 all'indirizzo 0x48000018 in memoria
// quell'indirizzo corrisponde fisicamente a un pin del microcontrollore
```

È esattamente lo stesso meccanismo dei puntatori — solo che l'indirizzo punta a hardware invece che a RAM.

---
