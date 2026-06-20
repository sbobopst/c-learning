# OPERATORI BITWISE

| Operatore | Nome | Comportamento |
|---|---|---|
| `&` | AND | 1 solo se entrambi i bit sono 1 |
| `\|` | OR | 1 se almeno un bit è 1 |
| `^` | XOR | 1 se i bit sono diversi tra loro |
| `~` | NOT | inverte tutti i bit |
| `<<` | shift sinistro | sposta i bit a sinistra |
| `>>` | shift destro | sposta i bit a destra |

## `valore << N`

```c
1 << 3    = 0b00000001 = 0b00001000     // maschera bit 3
10 << 1   = 0b00001010 = 0b00010100
```

### SET — accendere il bit N

```c
reg |= (1U << N);
```

```
  reg            0 0 0 0 0 0 0 0
  1U<<3          0 0 0 0 1 0 0 0
  OR (|)         ───────────────
  risultato      0 0 0 0 1 0 0 0
```

### CLEAR — spegnere il bit N

```c
reg &= ~(1U << N);
```

```
  reg                 0 0 0 0 1 0 0 0
  NOT(1U<<3)          1 1 1 1 0 1 1 1
  AND (&)             ───────────────
  risultato           0 0 0 0 0 0 0 0
```

### TOGGLE — invertire il bit N

```c
reg ^= (1U << N);
```

```
  reg              0 0 0 0 1 0 0 0
  (1U<<3)          1 1 1 1 0 1 1 1
  XOR (^)          ───────────────
  risultato        0 0 0 0 1 0 0 0
```

```
  reg              0 0 0 0 1 0 0 0
  (1U<<3)          1 1 1 1 1 1 1 1
  XOR (^)          ───────────────
  risultato        0 0 0 0 0 0 0 0
```

Lo XOR con la maschera inverte solo i bit che sono diversi tra loro, (1^1=0, 0^0=0, RESTANTE=1)

### READ — leggere il bit N

```c
int valore = (reg >> N) & 1;
```

shift a destra di N posizioni

```
reg = 0b00101000, leggo il bit 5:

reg >> 5   = 0b00000001   (il bit 5 ora è in posizione 0)
& 1        = 0b00000001   → 1
```

---


## Overflow quando si shifta oltre i bit disponibili

```c
uint8_t reg = 0;
reg |= (1 << 10);   // bit 10 non esiste in un uint8_t (8 bit: posizioni 0–7)
```

`1 << 10` viene calcolato come `int` a 32 bit (valore 1024), poi troncato a 8 bit quando assegnato a `reg`. Il risultato troncato è `0` — l'operazione non ha alcun effetto, **senza errore di compilazione**.

Regola pratica: il tipo del registro deve coprire il range di bit usato.

```c
uint8_t   reg8;    // bit validi: 0–7
uint16_t  reg16;   // bit validi: 0–15
uint32_t  reg32;   // bit validi: 0–31
```

---

## `1U` invece di `1` negli shift

`1` è un `int` con segno. Quando lo shift su tipi con segno tocca il bit più significativo, il comportamento può diventare undefined in C. `1U` è `unsigned int` — niente segno, lo shift è sempre ben definito.

```c
reg |= (1U << N);   // forma corretta, standard nel firmware
reg |= (1 << N);    // funziona nella maggior parte dei casi, ma meno sicuro
```

---

## `uint8_t`, `uint16_t`, `uint32_t` — tipi a dimensione fissa

### Il problema con `int` e `char`

In C, tipi come `int`, `char`, `long` **non hanno una dimensione fissata dallo standard** — dipendono dall'architettura e dal compilatore:

```c
int x;    // potrebbe essere 2, 4 o 8 byte a seconda della piattaforma
```

Su PC `int` è quasi sempre 4 byte, ma su un microcontrollore a 8 bit potrebbe essere diverso. Per codice firmware, dove devi sapere **esattamente** quanti bit occupa un registro, questa incertezza è inaccettabile — un registro hardware ha una dimensione fisica precisa (8, 16 o 32 bit) e il tuo tipo in C deve corrisponderle esattamente.

### La soluzione — tipi a dimensione esplicita

La libreria `<stdint.h>` definisce tipi il cui nome dichiara esattamente quanti bit occupano, su **qualsiasi** piattaforma:

```c
#include <stdint.h>

uint8_t   a;   // unsigned, 8 bit  (0 – 255)
uint16_t  b;   // unsigned, 16 bit (0 – 65535)
uint32_t  c;   // unsigned, 32 bit (0 – 4294967295)
uint64_t  d;   // unsigned, 64 bit

int8_t    e;   // signed, 8 bit   (-128 – 127)
int16_t   f;   // signed, 16 bit
int32_t   g;   // signed, 32 bit
```

### Come leggere il nome

```
uint8_t
^^^  ^  ^
|    |  └─ _t = "type", convenzione per indicare un typedef
|    └──── numero di bit
└───────── u = unsigned (nessun segno, solo valori positivi)
            assenza di "u" = con segno (es. int8_t)
```

### Perché "unsigned" conta nel firmware

Un registro hardware non ha "numeri negativi" — è una sequenza di bit, ogni bit rappresenta lo stato fisico di un pin o una configurazione. Usare un tipo `unsigned` evita ambiguità: tutti i bit sono usati per rappresentare il valore, nessuno è riservato al segno.

### Corrispondenza diretta con l'hardware

Questo è il motivo per cui userai sempre `uint8_t`/`uint16_t`/`uint32_t` nel firmware invece di `int`/`char`:

```c
uint8_t  reg8;     // corrisponde esattamente a un registro hardware a 8 bit
uint32_t GPIOA_ODR; // corrisponde esattamente a un registro hardware a 32 bit
```

Con `int` o `char` non avresti questa garanzia — il tuo codice potrebbe comportarsi diversamente compilato su piattaforme diverse, perché la dimensione di quei tipi non è fissa.

### Tabella riassuntiva

| Tipo | Bit | Range (unsigned) | Uso tipico |
|---|---|---|---|
| `uint8_t` | 8 | 0 – 255 | registro/pin a 8 bit, byte singolo |
| `uint16_t` | 16 | 0 – 65535 | registro a 16 bit, valori sensore |
| `uint32_t` | 32 | 0 – 4294967295 | registro STM32 (es. `GPIOx->ODR`) |

## Codice finale

[bitwise.c](bitwise.c)



