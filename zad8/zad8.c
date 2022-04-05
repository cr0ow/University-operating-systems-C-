#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mqueue.h>
#include <signal.h>
#include "libmq.h"

mqd_t des;

void unlink_at()
{
    mqclose(des);
    mqunlink(name);
    printf("Porzadki zrobione\n");
}

void handler(int n)
{
    mqclose(des);
    mqunlink(name);
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

    struct mq_attr attr;
    attr.mq_flags=0;
    attr.mq_maxmsg=10;
    attr.mq_msgsize=500;
    des=create(name, O_RDONLY | O_CREAT | O_EXCL, 0666, &attr);
    char komunikat[500];
    char nameK[9];
    mqd_t desK;
    int wynik;
    int pid, l, p;
    char dzialanie;
    char odeslane[400];
    

    printf("*KOLEJKA SERWERA*\n");
    printf(" maksymalna liczba komunikatów: %ld\n",attr.mq_maxmsg);
    printf(" Maksymalny rozmiar komunikatu: %ld\n",attr.mq_msgsize);

    while(1)
    {
        receive(des,komunikat,500,NULL);
        sscanf(komunikat,"%d:%d%c%d",&pid,&l,&dzialanie,&p);
        printf("Odczytalem komunikat: %s\n",komunikat);
        sprintf(nameK,"/%d",pid);
        desK=mqopen(nameK,O_WRONLY);
        switch(dzialanie)
        {
            case '+':
                wynik=l+p;
                break;
            case '-':
                wynik=l-p;
                break;
            case '*':
                wynik=l*p;
                break;
            case '/':
                wynik=l/p;
                break;
            default:
                perror("Bledne dzialanie");
                exit(EXIT_FAILURE);
        }
        sprintf(odeslane,"%d",wynik);
        send(desK,odeslane,400,1);
        mqclose(desK);
    }
    return 0;
}

