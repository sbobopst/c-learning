main: gpio.o main.o
	gcc gpio.o main.o -o main
gpio.o: gpio.c gpio.h
	gcc -c gpio.c -o gpio.o
main.o: main.c gpio.h
	gcc -c main.c -o main.o
clean:
	rm -f *.o 
