## Struct e typedef

### Concetti coperti

- `struct` per raggruppare dati correlati
- `typedef` per rinominare un tipo
- Accesso ai campi con `.` (diretto) e `->` (tramite puntatore)
- `const char *` per stringhe in sola lettura
- `strcpy` per copiare stringhe in una struct
- Array di struct
- Validazione dei valori in ingresso

---

## Perché struct

Finora ogni dato era una variabile separata. Nel firmware reale i dati sono correlati — un GPIO ha nome, numero di pin e stato. Tenerli separati è fragile:

```c
// senza struct — dati scollegati, facile sbagliare
char nome[32];
int pin;
int state;

// ✅ con struct — un oggetto coerente
typedef struct {
    char name[32];
    int pin;
    int state;
} GPIO_pin;
```

---

## Accesso ai campi — `.` vs `->`

| Sintassi | Quando usarla |
|---|---|
| `led.state` | Accesso diretto alla variabile |
| `g->state` | Accesso tramite puntatore — equivale a `(*g).state` |

```c
GPIO_pin led;
led.state = 1;           // accesso diretto

GPIO_pin *g = &led;
g->state = 1;            // tramite puntatore 
(*g).state = 1;          // equivalente, meno leggibile
```

`->` esiste perché `(*g).campo` è scomodo. Nel firmware HAL lo trovi ovunque:

```c
// dalla HAL STM32
GPIOx->BSRR = GPIO_Pin;   // scrive direttamente al registro hardware
```

---

## `const char *` — perché non `char *`

I letterali stringa (`"LED_VERDE"`) sono memorizzati in una zona **read-only** del programma (segmento `.rodata`). Modificarli causa un crash.

```c
void gpio_init(GPIO_pin *g, char *name, ...)        // warning: discards const
void gpio_init(GPIO_pin *g, const char *name, ...)  // contratto esplicito
```

`const char *name` significa: *"ricevo un puntatore a caratteri che non modificherò"*. Il compilatore fa rispettare il contratto:

```c
name[0] = 'X';          //  errore di compilazione — const protegge
strcpy(g->name, name);  //  legge da name, non scrive
```

### Le tre forme di const con puntatori

```c
const char *name          // contenuto const, puntatore no → puoi fare name++
char * const name         // puntatore const, contenuto no → puoi fare *name = 'X'
const char * const name   // entrambi const — né puntatore né contenuto modificabili
```

Nel firmware userai quasi sempre `const char *` — stai ricevendo una stringa da leggere.

---

## `strcpy` — copiare una stringa in una struct

Non puoi assegnare una stringa con `=` a un array di char. Devi usare `strcpy`:

```c
strcpy(g->name, name);    //  copia la stringa byte per byte fino a \0
g->name = name;           //  errore — non puoi assegnare array in C
strcpy(g->name, *name);   //  *name è il primo carattere, non la stringa
```

`strcpy(dest, src)` vuole due puntatori — indirizzi di partenza. `*name` dereferenzia il puntatore restituendo un `char` (il primo carattere), non un indirizzo.

---

## Codice finale

[pt2-gpio-sim-struct.c](./pt2-gpio-sim-struct.c)

A differenza di [pt1-gpio-sim-struct.c](./pt1-gpio-sim-struct.c) viene inclusa una funzione per inizializzare.

## Considerazione

Il codice non è ancora sicuro e robusto, ad esempio pin stati e altro possono avere valori casuali (stato = -99).