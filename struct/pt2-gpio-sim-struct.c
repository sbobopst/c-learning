#include <stdio.h>
#include <string.h>

typedef struct{
    char name[32];
    int pin;
    int state;
}GPIO_pin;

/* PARZIALMENTE ERRATO: char *name conviene definirlo con const, essendo char* in generale un letterale read-only 
ovvero il contenuto *n non può essere modificato.
In genere ti verrà generato un warning o meno, ma per correttezza va dichiarato const.
In questo modo il puntatore è anch esso const (non spostabile) il che è corretto logicamente */
//void gpio_init(GPIO_pin *g, char *name, int pin, int state){

/* CORRETTO: */
    void gpio_init(GPIO_pin *g, const char *name, int pin, int state){
    /* ERRATO: stai passando indirizzo del primo carattere */
    //strcpy(g->name, *name);
    
    /* CORRETTO: stai passando indirizzo della stringa intera */
    strcpy(g->name, name);
    
    g->pin = pin;
    g->state = state;
}

void set_high(GPIO_pin *g){
    g->state = 1;
}

void set_low(GPIO_pin *g){
    g->state = 0;
}

void print_state(GPIO_pin *g){
    printf("NAME_PIN:%s\nNUMBER_PIN:%d\nSTATE_PIN:%s\n\n", g->name, g->pin, (g->state ? "HIGH":"LOW"));
} 

int main(){
    GPIO_pin pin[3];
    gpio_init(&pin[0], "LED_ROSSO", 2, 0);
    gpio_init(&pin[1], "LED_VERDE", 4, 1);
    gpio_init(&pin[2], "LED_BLU", 9, 1);
    size_t dim = sizeof(pin) / sizeof(GPIO_pin);
    for(int i=0; i<dim; i++){
        print_state(&pin[i]);
    } 
    for(int i=0; i<dim; i++){
        set_low(&pin[i]);
        print_state(&pin[i]);
    } 
    
    return 0;
}