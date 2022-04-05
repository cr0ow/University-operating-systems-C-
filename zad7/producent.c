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
    wpd->wstaw=0;
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
    int zrodlo=open(argv[4],O_RDONLY,0644);
    int val;
    int n=NELE;

    while(bajty)
    {
        printf("PRODUCENT POZA SEKCJA KRYTYCZNA\n");
        printf("Wartosc iteratora wstaw: %d\n",wpd->wstaw);
        printf("Wartosc semafora: %d\n",sem_getval(semP,&val));
        printf("Do pamieci dzielonej:\n");
        if(bajty<NELE)
        {
            towar.buf=malloc(bajty);
            n=bajty;
        }
        read(zrodlo,towar.buf,n);
        write(STDOUT_FILENO,towar.buf,n);
        bajty-=n;
        printf("\nWstawionych bajtow: %d\n\n",n);

        sem_action(semP,2);
        printf("    PRODUCENT W SEKCJI KRYTYCZNEJ\n");
        printf("    Wartosc iteratora wstaw: %d\n",wpd->wstaw);
        printf("    Wartosc semafora: %d\n\n",sem_getval(semP,&val));
        for(int i=0; i<n; i++) wpd->buf[wpd->wstaw][i]=*(towar.buf+i);
        wpd->wstaw=(wpd->wstaw+1)%NBUF;
        sem_action(semK,1);
    }

    sem_close_(semP);
    sem_close_(semK);
    _munmap(wpd,sizeof(SegmentPD));
    _close(des);
    return 0;
}