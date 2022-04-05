run:
	gcc -Wall zad8.c -o serwer.x -L. -lmq -lrt
	gcc -Wall klient.c -o klient.x -L. -lmq -lrt
	xterm -hold -title SERWER -bg red -e ./serwer.x &
	xterm -hold -title KLIENT1 -e ./klient.x &
	xterm -hold -title KLIENT2 -e ./klient.x &

lib:
	gcc -c functions.c -o functions.o
	ar rcs libmq.a functions.o

clean:
	rm -rf *.x *.o

zip:
	zip zad8.zip zad8.c klient.c functions.c libmq.a libmq.h Makefile README.txt