## Perché separare il codice in più file

Finora ogni progetto è stato un singolo `.c`. Funziona per programmi piccoli, ma diventa ingestibile quando:

- vuoi riusare lo stesso codice (es. `gpio.c`) in più progetti diversi
- più persone lavorano sullo stesso progetto contemporaneamente
- il progetto cresce a decine o centinaia di file, come in un firmware reale

La soluzione standard in C è separare **dichiarazione** e **implementazione** in due file distinti.

---

## Header (`.h`) vs Source (`.c`)

### Header — solo dichiarazioni

```c
// gpio.h
#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

void print_reg(uint8_t reg);
void set_bit(uint8_t *reg, int n);
void clear_bit(uint8_t *reg, int n);
void toggle_bit(uint8_t *reg, int n);
int  read_bit(uint8_t reg, int n);

#endif
```

L'header contiene solo le **firme** delle funzioni — nome, tipo di ritorno, parametri. Nessun corpo, nessuna implementazione.

### Source — implementazione vera

```c
// gpio.c
#include "gpio.h"
#include <stdio.h>

void print_reg(uint8_t reg) {
    printf("reg 0b: ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (reg >> i) & 1);
    }
    printf("\n");
}

void set_bit(uint8_t *reg, int n) {
    *reg |= (1U << n);
}

void clear_bit(uint8_t *reg, int n) {
    *reg &= ~(1U << n);
}

void toggle_bit(uint8_t *reg, int n) {
    *reg ^= (1U << n);
}

int read_bit(uint8_t reg, int n) {
    return (reg >> n) & 1;
}
```


## Include guard — evitare doppie dichiarazioni

### Il problema senza guard

Il preprocessore tratta `#include` come un copia-incolla testuale letterale. Se lo stesso header finisse incluso due volte nello stesso file (anche indirettamente, tramite altri header), il compilatore vedrebbe le stesse dichiarazioni due volte e darebbe errore: *"redefinition of ..."*.

### La soluzione

```c
#ifndef GPIO_H
#define GPIO_H

// ... contenuto ...

#endif
```

Si legge:

```
#ifndef GPIO_H   →  "SE il simbolo GPIO_H non è ancora definito..."
#define GPIO_H   →  "...definiscilo subito, così la prossima volta sai di essere già stato qui"
   contenuto
#endif           →  fine del blocco condizionale
```

**Prima inclusione:** `GPIO_H` non esiste → il blocco viene eseguito, `GPIO_H` viene definito, il contenuto viene inserito.

**Inclusioni successive:** `GPIO_H` esiste già → il blocco viene saltato, il contenuto non viene inserito una seconda volta.

### Il nome della macro è arbitrario

`GPIO_H` non ha nessun collegamento automatico col nome del file `gpio.h` — è solo una convenzione tra programmatori. Il preprocessore cerca il file `gpio.h` sul disco per `#include`, ma la macro guardia `GPIO_H` potrebbe chiamarsi in qualsiasi modo. L'unico requisito è che sia **univoca in tutto il progetto** — se due header diverse usassero per errore la stessa macro guardia, il secondo header risulterebbe silenziosamente vuoto quando incluso dopo il primo.

Convenzione standard: nome del file in maiuscolo, punti sostituiti da underscore:

```
gpio.h        →  GPIO_H
motor_ctrl.h  →  MOTOR_CTRL_H
sensor_i2c.h  →  SENSOR_I2C_H
```

## `<>` vs `""` negli `#include`

| Sintassi | Dove cerca | Uso tipico |
|---|---|---|
| `<nome.h>` | Cartelle di sistema (es. `/usr/include/`) | Librerie standard: `stdio.h`, `stdint.h`, `string.h` |
| `"nome.h"` | Prima la cartella del progetto, poi le cartelle di sistema | Header personali del progetto: `gpio.h` |

```c
#include <stdint.h>   // libreria standard
#include "gpio.h"     // tuo file nel progetto
```

---

## Compilazione manuale multi-file

```bash
gcc -c gpio.c -o gpio.o      # compila gpio.c in object file (codice macchina, non eseguibile)
gcc -c main.c -o main.o      # compila main.c in object file
gcc gpio.o main.o -o main   # linking: unisce i due .o in un eseguibile
./programma
```

`-c` significa *"compila ma non collegare"* — produce un `.o` (object file), che contiene codice macchina ma riferimenti non ancora risolti alle funzioni definite altrove. Il **linker** (l'ultimo comando, senza `-c`) unisce tutti gli `.o` e risolve quei riferimenti, producendo l'eseguibile finale.

---

## Makefile — automatizzare la compilazione

Digitare 3 comandi `gcc` ogni volta è scomodo, e diventa impraticabile con decine di file. Il `Makefile` automatizza tutto.

### Sintassi base

```makefile
target: dipendenze
	comando
```

Si legge: *"per costruire `target`, assicurati che `dipendenze` esistano e siano aggiornate (costruendole ricorsivamente se serve), poi esegui `comando`"*.

⚠️ **Le righe sotto ogni regola devono iniziare con un carattere TAB**, non con spazi. È una delle cause più comuni di errore (*"missing separator"*) — molti editor convertono i tab in spazi automaticamente, quindi va verificato.

### Il Makefile completo

```makefile
programma: gpio.o main.o
	gcc gpio.o main.o -o programma

gpio.o: gpio.c gpio.h
	gcc -c gpio.c -o gpio.o

main.o: main.c gpio.h
	gcc -c main.c -o main.o

clean:
	rm -f *.o 
```

Il primo target nel file (`main`) è quello costruito di default quando lanci `make` senza argomenti.

### Esecuzione

```bash
make           # costruisce "programma"
./main
make clean     # rimuove tutti i file generati (.o)
```

## Perché l'header compare tra le dipendenze nel Makefile

```makefile
gpio.o: gpio.c gpio.h
	gcc -c gpio.c -o gpio.o
```

A prima vista sembra ridondante: il comando `gcc -c gpio.c -o gpio.o` non menziona `gpio.h` da nessuna parte. Eppure è elencato come dipendenza. Sono due meccanismi distinti, che lavorano su livelli diversi.

### Cosa fa il preprocessore

Quando gcc compila `gpio.c`, il preprocessore espande tutti gli `#include` presenti **dentro** `gpio.c`:

```c
// gpio.c
#include "gpio.h"   // gpio.c include gpio.h, non main.c
#include <stdio.h>
```

`gpio.h` viene quindi letto e inserito automaticamente durante la compilazione — gcc lo trova da solo seguendo l'`#include` nel sorgente, senza che serva specificarlo nella riga di comando.

### Cosa controlla `make`

La riga `gpio.o: gpio.c gpio.h` non dice a gcc cosa includere — dice a **`make`** quali file controllare per decidere se `gpio.o` va ricostruito. `make` confronta le date di modifica:

```
gpio.o è più vecchio di gpio.c?  → se sì, ricompila
gpio.o è più vecchio di gpio.h?  → se sì, ricompila
```

### Il caso che dimostra perché serve

Immagina di modificare **solo** `gpio.h` — ad esempio aggiungendo una nuova dichiarazione, senza toccare `gpio.c`:

```c
// gpio.h modificato
void reset_reg(uint8_t *reg);   // nuova dichiarazione
```

Se nel Makefile `gpio.h` non fosse elencato come dipendenza:

```makefile
gpio.o: gpio.c          ← gpio.h NON elencato
	gcc -c gpio.c -o gpio.o
```

`make` guarderebbe solo la data di `gpio.c` — non modificata — e concluderebbe che `gpio.o` è già aggiornato, saltando la ricompilazione. Il contenuto effettivo di `gpio.c`, una volta espanso con l'header aggiornato, sarebbe però cambiato: `gpio.o` resterebbe vecchio, con il rischio di bug silenziosi o errori di linking poco chiari più avanti.

Con `gpio.h` correttamente elencato, `make` rileva che è più recente di `gpio.o` e ricompila, anche se `gpio.c` non è stato toccato.

## Ricompilazione selettiva

`make` controlla le date di modifica dei file. Se modifichi solo `main.c` e rilanci `make`, viene ricompilato **solo** `main.o` — `gpio.o` non viene toccato, perché `gpio.c` non è cambiato.

```
make (prima volta):
  gcc -c gpio.c -o gpio.o    ← compilato
  gcc -c main.c -o main.o    ← compilato
  gcc gpio.o main.o -o programma   ← linkato

[modifichi solo main.c]

make (seconda volta):
  gcc -c main.c -o main.o    ← solo questo viene ricompilato
  gcc gpio.o main.o -o programma   ← re-linkato con il nuovo main.o
```

Su un progetto firmware con centinaia di file, questo fa la differenza tra aspettare pochi secondi o diversi minuti ogni volta che si cambia una riga di codice.