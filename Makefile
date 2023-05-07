all: main.o Functions.o
	gcc main.o Functions.o -o main
main.o: main.c Structures.h Functions.h
	gcc -c -std=c99 main.c
Functions.o: Functions.c Structures.h
	gcc -c -std=c99 Functions.c
clean:
	rm -rf *.o all
