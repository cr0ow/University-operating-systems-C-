#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mqueue.h>
#include <signal.h>
#include <unistd.h>
#include "libmq.h"

mqd_t desK, desS;

int main()
{
    sleep(1);
    char nameK[9];
    char dzialanie[400];
    char komunikat[500];
    char odebrany[500];
    int length,j;
    sprintf(nameK,"/%d",getpid());
    struct mq_attr attr;
    attr.mq_flags=0;
    attr.mq_maxmsg=10;
    attr.mq_msgsize=500;
    desK=create(nameK, O_RDONLY | O_CREAT | O_EXCL , 0666, &attr);
    desS=mqopen(name,O_WRONLY);

    printf("PID: %d\n",getpid());
    printf("*KOLEJKA KLIENTA*\n");
    printf(" maksymalna liczba komunikatów: %ld\n",attr.mq_maxmsg);
    printf(" Maksymalny rozmiar komunikatu: %ld\n",attr.mq_msgsize);

   while(fgets(dzialanie,400,stdin))
    {
        sprintf(komunikat,"%d:%s",getpid(),dzialanie);
        j=0;
        length=0;
        while(komunikat[j]!='\0') 
        {
            length++;
            j++;
        }
        send(desS,komunikat,length+1,1);
        receive(desK,odebrany,500,NULL);
        printf("wynik=%s\n",odebrany);
    }
    mqclose(desK);
    mqunlink(nameK);
    return 0;
}