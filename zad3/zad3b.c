#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int main(int argc, char **argv)
{
    if(argc!=4)
    {
        perror("nieprawidlowa liczba argumentow");
        exit(EXIT_FAILURE);
    }
    int sygnal=atoi(argv[2]);
    if(sygnal<1 || sygnal>64)
    {
        perror("podano niepoprawny sygnal");
        exit(EXIT_FAILURE);
    }
    int akcja=atoi(argv[3]);
    if(!(akcja==1 || akcja==2 || akcja==3))
    {
        perror("podano nieprawidlowa akcje");
        exit(EXIT_FAILURE);
    }

    char *pre = malloc(2 * sizeof(char));
    char *nazwa = malloc((sizeof *argv[1]/sizeof argv[1]) * sizeof(char));
    strcpy(pre,"./");
    strcpy(nazwa,argv[1]);
    char *plik = strcat(pre,nazwa);
    int pid=fork();
    switch(pid)
    {
        case -1:
            perror("fork error");
            exit(EXIT_FAILURE);
        case 0:
            execl(plik, argv[1], argv[2], argv[3], NULL);
            perror("execl error");
            _exit(EXIT_FAILURE);
        default:
            sleep(1);
            while((kill(pid,0)==0) && (sygnal!=0))
            {
                sleep(1);
                printf("Podaj numer sygnalu (0 aby zakonczyc program): ");
                scanf("%d",&sygnal);
                if(sygnal!=0) kill(pid,sygnal);   
            }
            break;
    }
    free(pre);
    free(nazwa);
    return 0;
}
