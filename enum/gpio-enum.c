#include <stdio.h>
#include <string.h>

typedef enum{
    GPIO_LOW = 0,
    GPIO_HIGH = 1
}GPIO_state;

typedef struct{
    char name[32];
    int pin;
    GPIO_state state;
}GPIO_pin;

int gpio_init(GPIO_pin *g, const char *name, int pin, GPIO_state state){
    if(state != GPIO_LOW && state != GPIO_HIGH) return -1;
    strcpy(g->name, name);
    g->pin = pin;
    g->state = state;
    return 0;
}

void set_high(GPIO_pin *g){
    g->state = GPIO_HIGH;
}

void set_low(GPIO_pin *g){
    g->state = GPIO_LOW;
}

void print_state(GPIO_pin *g){
    printf("NAME_PIN:%s\nNUMBER_PIN:%d\nSTATE_PIN:%s\n\n", g->name, g->pin, (g->state ? "HIGH":"LOW"));
} 

int main(void) {
    GPIO_pin pin[3]; 
    if (gpio_init(&pin[0], "LED_ROSSO", 1, GPIO_LOW)  != 0) { printf("Errore pin 0\n"); return 1; }
    if (gpio_init(&pin[1], "LED_VERDE", 4, GPIO_HIGH) != 0) { printf("Errore pin 1\n"); return 1; }
    
    /* Il programma si interrompe qui, a causa di state = 23*/
    if (gpio_init(&pin[2], "LED_BLU",   9, 23) != 0) { printf("Errore pin 2\n"); return 1; }

    size_t dim = sizeof(pin) / sizeof(GPIO_pin);
    for (int i = 0; i < dim; i++) {
        print_state(&pin[i]);
    }
    return 0;
}