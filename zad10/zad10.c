#define _REENTRANT
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

int watki, sekcje;
bool* wybieranie;
int* numer;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int licznik=0;

int max(int a[])
{
    int b=0;
    for(int i=0; i<watki; i++) if(a[i]>b) b=a[i];
    return b;
}

bool compare(int numer1, int j, int numer2, int i)
{
    if(numer1 < numer2) return true;
    if(numer1==numer2 && j<i) return true;
    return false;
}

void* pthread(void* p)
{
    int licz=0;
    int* iD=(int *)p;
    
    for(int i=0; i<sekcje; i++)
    {
        
        wybieranie[*iD]=true;
        numer[*iD]=max(numer)+1;
        wybieranie[*iD]=false;

        printf("**SEKCJA PRYWATNA**\n");
        printf("Watek o id: %d\n",*iD+1);
        printf("Otrzymany numer: %d\n\n",numer[*iD]);
        for(int j=0; j<watki; j++)
        {
            while(wybieranie[j]);
            while(numer[j]!=0 && compare(numer[j],j,numer[*iD],*iD));
        }

        printf("%d\n",*iD);
        licz=licznik;
        licz++;
        sleep(3);
        licznik=licz;
        numer[*iD]=0;
        
        printf("\t\t\t\t\t\t**SEKCJA KRYTYCZNA**\n");
        printf("\t\t\t\t\t\tWatek o id: %d\n",*iD+1);
        printf("\t\t\t\t\t\tWartosc globalnego licznika: %d\n\n",licznik);
    }
    return NULL;
}

int main(int argc, char** argv)
{
    watki=atoi(argv[1]);
    sekcje=atoi(argv[2]);

    wybieranie=(bool *)calloc(watki,sizeof(bool));
    for(int i=0; i<watki; i++) wybieranie[i]=false;

    numer=(int *)calloc(watki,sizeof(int));
    for(int i=0; i<watki; i++) numer[i]=0;
    
    pthread_t watek[watki];
    int id[watki];

    for(int i=0; i<watki; i++)
    {
        id[i]=i;
        if(pthread_create(&watek[i],NULL,pthread,(void *)&id[i])!=0)
        {
            perror("Blad funkcji pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for(int i=0; i<watki; i++)
    {
        if(pthread_join(watek[i],NULL)!=0)
        {
            perror("Blad funkcji pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    printf("Rzeczywista wartosc licznika: %d\n",licznik);
    printf("Przewidywana wartosc licznika: %d\n",watki*sekcje);
    free(wybieranie);
    free(numer);
    return 0;
}