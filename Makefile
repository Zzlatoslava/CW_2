all: main.o Functions.o
	gcc  main.o Functions.o -o main -lm
main.o: main.c Structures.h Functions.h
	gcc -c  main.c -lm
Functions.o: Functions.c Structures.h
	gcc -c  Functions.c -lm
clean:
	rm -rf *.o all
