all: main.o Functions.o
	gcc -lm main.o Functions.o -o main -lm
main.o: main.c Structures.h Functions.h
	gcc -c -std=c99 -lm main.c -lm
Functions.o: Functions.c Structures.h
	gcc -c -std=c99 -lm Functions.c -lm
clean:
	rm -rf *.o all
