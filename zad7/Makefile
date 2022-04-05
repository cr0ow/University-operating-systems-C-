static: libstatic
	gcc -pthread -Wall -std=gnu99 -pedantic -o producent.x producent.c -L. -lstat -lrt
	gcc -pthread -Wall -std=gnu99 -pedantic -o konsument.x konsument.c -L. -lstat -lrt
	gcc -pthread -Wall -std=gnu99 -pedantic -o zad7.x zad7.c -L. -lstat -lrt
	./zad7.x producent.x konsument.x 
	diff -s zrodlo.txt wynik.txt

shared: libshared
	gcc -o producent.x -lpthread -Wall -std=gnu99 -pedantic -O shm.o sem.o -L./lib -lsha -lpthread -lrt -Wl,-R ./lib
	gcc -o konsument.x -lpthread -Wall -std=gnu99 -pedantic -O shm.o sem.o -L./lib -lsha -lpthread -lrt -Wl,-R ./lib
	gcc -o zad7.x -lpthread -Wall -std=gnu99 -pedantic -O shm.o sem.o -L./lib -lsha -lpthread -lrt -Wl,-R ./lib
	./zad7.x producent.x konsument.x

libshared: obj
	gcc  -shared -o libsha.so -Wall -std=gnu99 -pedantic -O shm.o sem.o
	mkdir -p ./lib
	mv libsha.so ./lib

libstatic: obj
	ar rcs libstat.a shm.o sem.o
	mkdir -p ./lib
	mv libstat.a ./lib

obj:
	gcc -Wall -std=gnu99 -pedantic -c shm.c -o shm.o
	gcc -Wall -std=gnu99 -pedantic -c sem.c -o sem.o

clean:
	rm -rf *.x *.o

zip:
	zip zad7.zip zad7.c producent.c konsument.c shm.c sem.c shm.h sem.h Makefile README.txt