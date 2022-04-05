run-a:
	gcc -Wall -std=c99 -pedantic zad5a.c -o zad5a.x
	./zad5a.x ./potok
	diff -s zrodlo.txt wynik.txt

run-b:
	gcc -Wall -std=c99 -pedantic zad5b_p.c -o zad5b_p.x
	gcc -Wall -std=c99 -pedantic zad5b_k.c -o zad5b_k.x
	mkfifo -m 644 potok
	xterm -hold -title PRODUCENT -e ./zad5b_p.x potok &
	xterm -hold -title KONSUMENT -e ./zad5b_k.x potok &

check:
	diff -s zrodlo.txt wynik.txt
	rm -rf potok

clean:
	rm -rf *.x potok

zip:
	zip zad5.zip zad5a.c zad5b_p.c zad5b_k.c zrodlo.txt wynik.txt README.md Makefile