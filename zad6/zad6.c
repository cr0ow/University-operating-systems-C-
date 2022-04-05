#include "libsem.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <semaphore.h>
#include <string.h>

sem_t* sem;
char name[] = "/sem";

void unlink_at()
{
    sem_unlink(name);
}

void handler(int n)
{
    if(sem_unlink(name)==-1)
    {
        perror("Blad funkcji sem_unlink");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    char *pre = malloc(2 * sizeof(char));
    char *nazwa = malloc((sizeof *argv[1]/sizeof argv[1]) * sizeof(char));
    strcpy(pre,"./");
    strcpy(nazwa,argv[1]);
    char *plik = strcat(pre,nazwa);
   
    char file[] = "numer.txt";
    FILE* numer1 = fopen(file,"w+");
    fprintf(numer1,"%d",0);
    fclose(numer1);

    sem = sem_creat(name, O_CREAT | O_EXCL, 0644, 1);
    sem_close_(sem);

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
    
    int procesy=atoi(argv[2]);
    int sekcje=atoi(argv[3]);

    for(int i=0; i<procesy; i++)
    {
        switch(fork())
        {
            case -1:
                perror("fork error!");
                exit(EXIT_FAILURE);
            case 0:
                execl(plik,argv[1],name,argv[3],file,NULL);
                perror("execl error");
                _exit(2);
            default:
                sleep(7);
                break;
        }
    }
    for(int i=0; i<procesy; i++) wait(NULL);
    int num;
    FILE* numer2 = fopen(file,"r");
    fscanf(numer2,"%d",&num);
    printf("Numer zapisany w pliku: %d\n",num);
    printf("Przewidywany numer zapisany w pliku: %d\n",sekcje*procesy);
    fclose(numer2);
    sem_unlink_(name);
    return 0;
}