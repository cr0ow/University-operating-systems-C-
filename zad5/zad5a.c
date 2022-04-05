#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

char* fifo;

void zakoncz(void)
{
    if(unlink(fifo)==-1)
    {
        perror("Nie udalo sie usunac potoku!");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    fifo=argv[1];
    if(atexit(zakoncz)!=0)
    {
        perror("atexit error!");
        exit(EXIT_FAILURE);
    }

    if(argc!=2)
    {
        perror("Nieprawidlowa liczba argumentow");
        exit(EXIT_FAILURE);
    }

    if(mkfifo(fifo,0644)==-1)
    {
        perror("Blad funkcji mkfifo");
        exit(EXIT_FAILURE);
    }
    int des=open(fifo,O_RDWR,0644);

    FILE *zrodlo=fopen("zrodlo.txt","r");
    if(zrodlo==NULL)
    {
        perror("Blad otwarcia pliku");
        exit(EXIT_FAILURE);
    }
    if(fseek(zrodlo,0,SEEK_END)!=0)
    {
        perror("Blad funkcji fseek");
        exit(EXIT_FAILURE);
    }
    int bajty=ftell(zrodlo);
    fclose(zrodlo);
    int inout[2];
    inout[0]=open("wynik.txt",O_TRUNC | O_WRONLY,0644);
    if(inout[0]==-1)
    {
        perror("Blad funkcji open");
        exit(EXIT_FAILURE);
    }
    inout[1]=open("zrodlo.txt",O_RDONLY,0644);
    if(inout[1]==-1)
    {
        perror("Blad funkcji open");
        exit(EXIT_FAILURE);
    }
    int porcja1=400, porcja2=200;
    char *bufIN=malloc(porcja1);
    char *bufOUT=malloc(porcja2);
    int pozycja1=bajty, pozycja2=bajty;
    int pobrane, wczytane;
    srand(time(NULL));

    switch(fork())
    {
        case -1:
            perror("fork error");
            exit(EXIT_FAILURE);
        case 0:
            close(inout[1]);
            while(pozycja2>0)
            {
                pobrane=read(des,bufOUT,porcja2);
                if(pobrane<=0) break;
                write(STDOUT_FILENO,"Pobrano z potoku:\n",18);
                write(STDOUT_FILENO,bufOUT,pobrane);
                write(STDOUT_FILENO,"\n\n",2);
                if(write(inout[0],bufOUT,porcja2)==-1)
                {
                    perror("Blad funkcji write");
                    exit(EXIT_FAILURE);
                }
                pozycja2-=pobrane;
                if(porcja2>pozycja2)
                {
                    porcja2=pozycja2;
                    bufOUT=malloc(porcja2);
                }
            }
            break;
        default:
            close(inout[0]);
            while(porcja1>0)
            {
                wczytane=read(inout[1],bufIN,porcja1);
                write(STDOUT_FILENO,"Dodano do potoku:\n",18);
                write(STDOUT_FILENO,bufIN,wczytane);
                write(STDOUT_FILENO,"\n\n",2);
                if(write(des,bufIN,porcja1)==-1)
                {
                    perror("Blad funkcji write");
                    exit(EXIT_FAILURE);
                }
                pozycja1-=porcja1;
                if(porcja1>pozycja1) 
                {
                    porcja1=pozycja1;
                    bufIN=malloc(porcja1);
                }
                sleep(rand()%5);
            }
            wait(NULL);
            break;
    }
    return 0;
}