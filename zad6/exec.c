#include "libsem.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <time.h>

void nadpisz(char* file)
{
    int num;
    FILE* numer1 = fopen(file,"r");
    fscanf(numer1,"%d",&num);
    fclose(numer1);
    num++;
    sleep(rand()%3);
    FILE* numer2 = fopen(file,"w+");
    fprintf(numer2,"%d",num);
    fclose(numer2);
    printf("Zapisane!\n\n");
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    sem_t* sem = sem_open_(argv[1],O_RDWR);
    int val;
    int sekcje=atoi(argv[2]);
    for(int i=0; i<sekcje; i++)
    {
        printf("    PRZED SEKCJA KRYTYCZNA\n");
        printf("    PID procesu: %d\n",getpid());
        printf("    Wartosc semafora: %d\n\n",sem_getval(sem,&val));

        sem_action(sem,2);
        printf("W SEKCJI KRYTYCZNEJ\n");
        printf("PID procesu: %d\n",getpid());
        printf("Wartosc semafora: %d\n",sem_getval(sem,&val));
        nadpisz(argv[3]);

        sem_action(sem,1);
    }
    sem_close_(sem);
    return 0;
}