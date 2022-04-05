#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include "shm.h"
#include "sem.h"

int main(int argc, char **argv)
{
    int des=_open(argv[1],O_RDWR,0644);
    SegmentPD *wpd = (SegmentPD *) _map(NULL,sizeof(SegmentPD),PROT_READ | PROT_WRITE,MAP_SHARED,des,0);
    wpd->wyjmij=0;
    sem_t* semP=sem_open_(argv[2],O_RDWR);
    sem_t* semK=sem_open_(argv[3],O_RDWR);

    FILE *file=fopen("zrodlo.txt","r");
    if(file==NULL)
    {
        perror("Blad otwarcia pliku");
        exit(EXIT_FAILURE);
    }
    if(fseek(file,0,SEEK_END)!=0)
    {
        perror("Blad funkcji fseek");
        exit(EXIT_FAILURE);
    }
    int bajty=ftell(file);
    fclose(file);

    struct Towar towar={malloc(NELE)};
    int wynik=open(argv[4],O_WRONLY | O_TRUNC,0644);
    int val;
    int n=NELE;

    while(bajty)
    {
        sleep(1);
        sem_action(semK,2);
        printf("KONSUMENT W SEKCJI KRYTYCZNEJ\n");
        printf("Wartosc iteratora wyjmij: %d\n",wpd->wyjmij);
        printf("Wartosc semafora: %d\n\n",sem_getval(semK,&val));
        if(bajty<NELE)
        {
            towar.buf=malloc(bajty);
            n=bajty;
        }
        for(int i=0; i<n; i++) 
        {
            write(STDOUT_FILENO,wpd->buf[wpd->wyjmij]+i,1);
            *(towar.buf+i)=wpd->buf[wpd->wyjmij][i];
        }
        bajty-=n;
        wpd->wyjmij=(wpd->wyjmij+1)%NBUF;
        printf("\nPobranych bajtow: %d\n",n);

        sem_action(semP,1);
        printf("    KONSUMENT POZA SEKCJA KRYTYCZNA\n");
        printf("    Wartosc iteratora wyjmij: %d\n",wpd->wyjmij);
        printf("    Wartosc semafora: %d\n",sem_getval(semK,&val));
        printf("    Z pamieci dzielonej:\n");
        write(STDOUT_FILENO,towar.buf,n);
        write(wynik,towar.buf,n);
        printf("\n\n");
    }

    sem_close_(semP);
    sem_close_(semK);
    _unlink(argv[1]);
    _munmap(wpd,sizeof(SegmentPD));
    _close(des);
    return 0;
}