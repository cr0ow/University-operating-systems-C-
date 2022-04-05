#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char **argv)
{
    int des=open(argv[1],O_WRONLY,0644);
    if(des==-1)
    {
        perror("Nie udalo sie otworzyc potoku!");
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
    int inout=open("zrodlo.txt",O_RDONLY,0644);
    if(inout==-1)
    {
        perror("Blad funkcji open");
        exit(EXIT_FAILURE);
    }
    int porcja=400;
    char *buf=malloc(porcja);
    int pozycja=bajty;
    int wczytane;
    srand(time(NULL));

    while(pozycja>0)
    {
        wczytane=read(inout,buf,porcja);
        if(wczytane<=0) break;
        write(STDOUT_FILENO,"Dodano do potoku:\n",19);
        write(STDOUT_FILENO,buf,wczytane);
        write(STDOUT_FILENO,"\n\n",2);
        if(write(des,buf,porcja)==-1)
        {
            perror("Blad funkcji write");
            exit(EXIT_FAILURE);
        }
        pozycja-=wczytane;
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
