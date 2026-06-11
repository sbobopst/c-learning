#include <stdio.h>
#include <string.h>

typedef struct {
    char name[32];
    int pin;
    int state;
} GPIO_pin;

void set_pin(GPIO_pin *g){
    g->pin = 5;
}

void set_state(GPIO_pin *g){
    g->state=1;
}

void set_name(GPIO_pin *g){
    strcpy(g->name, "LED_VERDE");
}

void print_state(GPIO_pin *g){    
    // CORRETTO: printf("%s\n", (*g).name);
    /* FORMA MIGLIORE */
    printf("NAME_PIN:%s\nNUMBER_PIN:%d\nSTATE_PIN:%d\n", g->name, g->pin, g->state);
 }

int main(){
    GPIO_pin led;
    set_pin(&led);
    set_state(&led);
    set_name(&led);
    print_state(&led);
    return 0;
}