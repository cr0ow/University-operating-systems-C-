#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
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

    char *pre = malloc(2 * sizeof(char));
    char *nazwa = malloc((sizeof *argv[1]/sizeof argv[1]) * sizeof(char));
    strcpy(pre,"./");
    strcpy(nazwa,argv[1]);
    char *plik = strcat(pre,nazwa);

    int status[3];
    int pid[3];
    
    if(setpgid(0,0)==-1)
    {
        perror("setpgid error");
        exit(EXIT_FAILURE);
    }

    for(int i=1; i<65; i++)
    {
        if (i!=9 && i!=19 && i!=32 && i!=33 && signal(i,SIG_IGN)==SIG_ERR)
        {
            perror("ignore error");
            exit(EXIT_FAILURE);
        }
    }

    for(int i=0; i<3; i++)
    {
        switch(fork())
        {
            case -1:
                perror("fork error");
                exit(EXIT_FAILURE);
            case 0:
                execl(plik,argv[1], argv[2], argv[3], NULL);
                perror("execl error");
                _exit(EXIT_FAILURE);
            default:
                break;
        }
    }
    for(int i=0; i<3; i++) pid[i]=wait(&status[i]);
    for(int i=0; i<3; i++) printf("Status procesu %d: %d\n",i+1,pid[i]);
    free(pre);
    free(nazwa);
    return 0;
}
