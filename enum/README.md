## `enum` — leggibilità e manutenibilità

Abbiamo introdotto `enum` solo per il campo `state`, perché è l'unico campo con un insieme fisso e noto di valori validi: `LOW` o `HIGH`.

```c
typedef enum {
    GPIO_LOW  = 0,
    GPIO_HIGH = 1
} GPIO_state;
```

Senza enum il codice sarebbe:

```c
g->state = 1;   // cosa significa 1?
```

Con enum:

```c
g->state = GPIO_HIGH;   // chiaro e inequivocabile
```

Se domani `GPIO_HIGH` deve valere `2` invece di `1`, si cambia solo la definizione dell'enum — tutto il resto del codice si aggiorna automaticamente.

---

## Validazione con codice di ritorno

Poiché `state` ha solo due valori validi, `gpio_init` li controlla esplicitamente e restituisce `-1` se riceve qualcosa di diverso:

```c
int gpio_init(GPIO_pin *g, const char *name, int pin, GPIO_state state) {
    if (state != GPIO_LOW && state != GPIO_HIGH) return -1;
    strcpy(g->name, name);
    g->pin   = pin;
    g->state = state;
    return 0;   // successo
}
```

Il chiamante controlla il valore di ritorno e gestisce l'errore:

```c
if (gpio_init(&pin[2], "LED_BLU", 9, 33) != 0) {
    printf("Errore pin 2\n");
    return 1;
}
```

---

## Codice finale

[gpio-enum.c](./gpio-enum.c)