memory-pt2: arr.o memory-pt2.o
	gcc arr.o memory-pt2.o -o memory-pt2

arr.o: arr.c arr.h
	gcc -c arr.c -o arr.o

memory-pt2.o: memory-pt2.c arr.h
	gcc -c memory-pt2.c -o memory-pt2.o

clean:
	rm -f *.o memory-pt2