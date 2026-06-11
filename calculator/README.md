## Livello 1 — Calcolatrice da terminale

### Concetti coperti

- Tipi di base: `int`, `double`, `char`
- Input/output con `printf` e `scanf`
- Struttura condizionale `if / else if / else`
- Codici di uscita: `return 0` (successo), `return 1` (errore)
- Differenza tra `char` (`'+'`) e stringa (`"+"`)

### Codice finale
[calculator-pt2.c](./calculator-pt2.c)

### Compilazione ed esecuzione
```bash
gcc calculator-pt2.c -o calculator
./calculator
```

---

### Concetti chiave

#### `char` vs stringa
In C esistono due cose completamente diverse:

| Sintassi | Tipo | Cosa è |
|---|---|---|
| `'+'` | `char` | Un singolo byte — valore ASCII 43 |
| `"+"` | `char *` | Un puntatore a un array in memoria |

Per confrontare un `char` si usano **sempre** le virgolette singole:
```c
if (op == '+')   // corretto
if (op == "+")   // confronto char vs puntatore → warning del compilatore
```

#### `scanf` — formato senza virgole letterali
```c
scanf("%lf %c %lf", &a, &op, &b);   // lo spazio salta whitespace
scanf("%lf, %c, %lf", &a, &op, &b); // si aspetta virgole letterali nell'input
```

#### `printf` — un `%` per ogni argomento
```c
printf("%.2f\n", a + b);   // un segnaposto, un valore
printf("%.2f %.2f\n", a);  // due segnaposto, un solo valore → comportamento indefinito
```

#### `return` in `main`
```c
return 0;   // tutto ok — segnala successo al sistema operativo
return 1;   // errore — segnala fallimento
```
Su firmware questa stessa logica si applica ai codici di ritorno delle funzioni HAL (`HAL_OK`, `HAL_ERROR`).

---

