run: exec
	gcc -pthread -o zad6.x zad6.c -L. -lsem
	./zad6.x exec.x 5 4

exec:
	gcc -pthread -o exec.x exec.c -L. -lsem

lib:
	gcc -c functions.c -o functions.o
	ar rcs libsem.a functions.o

clean:
	rm -rf *.x *.o

zip:
	zip zad6.zip zad6.c exec.c functions.c libsem.h libsem.a Makefile README.txt
