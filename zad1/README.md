# Procesy

## Zadanie

![task](ex1.png)

## Zawartość

I.   Podpunkt a
    Program sklada sie z jednego modulu: 
    1) zad1a.c  - program glowny. 
II.  Podpunkt b
    Program sklada sie z jednego modulu: 
    1) zad1b.c  - program glowny. 
III. Podpunkt c
    Program sklada sie z jednego modulu: 
    1) zad1c.c  - program glowny.
IV.  Podpunkt d
    Program sklada sie z jednego modulu: 
    1) zad1d.c  - program glowny.
V.   Podpunkt e
    Program sklada sie z jednego modulu: 
    1) zad1e.c  - program glowny. 

## Uruchomienie

Katalog zawiera plik Makefile do kompilacji, czyszczenia oraz archiwizacji katalogu.

 - Aby uruchomic 1-szy program, nalezy wykonac komende:
       make run-a
 - Aby uruchomic 2-gi program, nalezy wykonac komende:
       make run-b
 - Aby uruchomic 3-ci program, nalezy wykonac komende:
       make run-c
 - Aby uruchomic 4-ty program, nalezy wykonac komende:
       make run-d
 - Aby uruchomic 5-ty program, nalezy wykonac komende:
       make run-e
 - Aby wyczyscic zawartosc katalogu (usunac zbedne pliki), nalezy wykonac:
       make clean

## Ile procesow powstanie przy n-krotnym wywolaniu funkcji fork i dlaczego?
Powstanie 2^n - 1 procesow (nie liczac procesu macierzystego), poniewaz kazdy
proces potomny staje sie kopia swojego rodzica, w tym przypadku jesli petli for pozostaly
juz tylko dwie iteracje to proces potomny rowniez przeprowadzi tylko dwie iteracje tej
petli, mimio ze w procesie macierzystym zadeklarowalismy, ze ma sie wykonac 3 razy.