#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


void handler(int sygnal)
{
    printf("Przechwycilem sygnal: %d\n",sygnal);
}

int main(int argc, char **argv)
{
    if(argc!=3)
    {   
        perror("nieprawidlowa liczba argumentow ");
        exit(EXIT_FAILURE);
    }
    int sygnal=atoi(argv[1]);
    if(sygnal<1 || sygnal>64)
    {
        perror("podano niepoprawny sygnal");
        exit(EXIT_FAILURE);
    }
    int akcja=atoi(argv[2]);
    if(!(akcja==1 || akcja==2 || akcja==3))
    {
        perror("podano nieprawidlowa akcje");
        exit(EXIT_FAILURE);
    }
    void (*han)(int);
    han=handler;

    //for potrzebny do zadania c
    for(int i=1; i<65; i++)
    {
        if (i!=9 && i!=19 && i!=32 && i!=33 && signal(i,SIG_DFL)==SIG_ERR)
        {
            perror("ignore error");
            exit(EXIT_FAILURE);
        }
    }
    
    //printf potrzebny do zadania a
    printf("Do wywolania polecenia kill uzyj PID: %d\n",getpid());
    
    while(1)
    {
        if (akcja==1 && signal(sygnal,SIG_DFL)==SIG_ERR)
        {
            perror("default error");
            exit(EXIT_FAILURE);
        }
        if (akcja==2 && signal(sygnal,SIG_IGN)==SIG_ERR)
        {
            perror("ignore error");
            exit(EXIT_FAILURE);
        }
        if (akcja==3 && signal(sygnal,han)==SIG_ERR)
        {
            perror("handler error");
            exit(EXIT_FAILURE);
        }
        pause();
    }
    return 0;
}