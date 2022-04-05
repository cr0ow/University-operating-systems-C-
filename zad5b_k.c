#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char **argv)
{
    int des=open(argv[1],O_RDONLY,0644);
    if(des==-1)
    {
        perror("Nie udalo sie otworzyc potoku");
        exit(-1);
    }
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
    int inout=open("wynik.txt",O_TRUNC | O_WRONLY,0644);
    if(inout==-1)
    {
        perror("Blad funkcji open");
        exit(EXIT_FAILURE);
    }
    int porcja=200;
    char *buf=malloc(porcja);
    int pozycja=bajty;
    int pobrane;
    srand(time(NULL));

    while(pozycja>0)
    {
        pobrane=read(des,buf,porcja);
        if(pobrane<=0) break;
        write(STDOUT_FILENO,"Pobrano z potoku:\n",18);
        write(STDOUT_FILENO,buf,pobrane);
        write(STDOUT_FILENO,"\n\n",2);
        if(write(inout,buf,porcja)==-1)
        {
            perror("Blad funkcji write");
            exit(EXIT_FAILURE);
        }
        pozycja-=pobrane;
        if(porcja>pozycja)
        {
            porcja=pozycja;
            buf=malloc(porcja);
        }
        sleep(rand()%5);
    }
    close(inout);
    return 0;
}
