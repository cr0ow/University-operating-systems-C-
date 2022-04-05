#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include <string.h>
#include "shm.h"
#include "sem.h"

sem_t* semP;
sem_t* semK;
SegmentPD *wpd;
int des;
const char name[]="/shm";
char nameP[] = "/semP";
char nameK[] = "/semK";

char* convert(char* name)
{
    char *pre = malloc(2 * sizeof(char));
    char *nazwa = malloc((sizeof *name/sizeof name) * sizeof(char));
    strcpy(pre,"./");
    strcpy(nazwa,name);
    return strcat(pre,nazwa);
}

void unlink_at()
{
    sem_close_(semP);
    sem_close_(semK);
    _munmap(wpd,sizeof(SegmentPD));
    _close(des);
    sem_unlink(nameP);
    sem_unlink(nameK);
    _unlink(name);
    printf("Porzadki zrobione\n");
}

void handler(int n)
{
    sem_close_(semP);
    sem_close_(semK);
    _munmap(wpd,sizeof(SegmentPD));
    _close(des);
    sem_unlink(nameP);
    sem_unlink(nameK);
    _unlink(name);
}

int main(int argc, char **argv)
{
    if(signal(SIGINT,handler)==SIG_ERR)
    {
        perror("Blad funkcji signal");
        exit(EXIT_FAILURE);
    }
    if(atexit(unlink_at)!=0)
    {
        perror("Blad funkcji atexit");
        exit(EXIT_FAILURE);
    }

    const char zrodlo[]="zrodlo.txt";
    const char wynik[]="wynik.txt";
    char* producent=convert(argv[1]);
    char* konsument=convert(argv[2]);
    
    des=_open(name,O_CREAT | O_EXCL | O_RDWR,0644);
    _length(des,sizeof(SegmentPD));
    wpd = (SegmentPD *) _map(NULL,sizeof(SegmentPD),PROT_READ | PROT_WRITE,MAP_SHARED,des,0);

    semP = sem_creat(nameP, O_CREAT | O_EXCL, 0644, 1);
    semK = sem_creat(nameK, O_CREAT | O_EXCL, 0644, 0);
    int val;
    
    printf("*SEMAFORY*\n");
    printf("  wartosc poczatkowa semafora producena: %d\n",sem_getval(semP,&val));
    printf("  wartosc poczatkowa semafora konsumenta: %d\n",sem_getval(semK,&val));
    printf("*PAMIEC DZIELONA*\n");
    printf("  rozmiar pamieci w bajtach: %ld\n",sizeof(SegmentPD));
    printf("  deskryptor: %d\n\n",des);

    switch(fork()) //producent
    {
        case -1:
            perror("fork error");
            exit(EXIT_FAILURE);
        case 0:
            execl(producent,argv[1],name,nameP,nameK,zrodlo,NULL);
            perror("execl error");
            _exit(EXIT_FAILURE);
        default:
            break;
    }
    switch(fork()) //konsument
    {
        case -1:
            perror("fork error");
            exit(EXIT_FAILURE);
        case 0:
            execl(konsument,argv[2],name,nameP,nameK,wynik,NULL);
            perror("execl error");
            exit(EXIT_FAILURE);
        default:
            break;
    }
    wait(NULL);
    wait(NULL);
    return 0;
}