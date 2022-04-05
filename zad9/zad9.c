#define _REENTRANT
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int watki, sekcje;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int licznik=0;

void* pthread(void* p)
{
    
    int licz=0;
    int* iD=(int *)p;
    
    for(int i=0; i<sekcje; i++)
    {
        printf("**SEKCJA PRYWATNA**\n");
        printf("Watek o id: %d\n",*iD);
        printf("Nr sekcji prywtnej: %d\n\n",i+1);
        
        pthread_mutex_lock(&mutex);

        licz=licznik;
        licz++;
        sleep(3);
        licznik=licz;
        printf("\t\t\t\t\t\t**SEKCJA KRYTYCZNA**\n");
        printf("\t\t\t\t\t\tWatek o id: %d\n",*iD);
        printf("\t\t\t\t\t\tNr sekcji krytycznej: %d\n",i+1);
        printf("\t\t\t\t\t\tWartosc globalnego licznika: %d\n\n",licznik);

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char **argv)
{ 
    watki=atoi(argv[1]);
    sekcje=atoi(argv[2]);
    
    pthread_t watek[watki];
    int id[watki];

    for(int i=0; i<watki; i++)
    {
        id[i]=i+1;
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
    if(pthread_mutex_destroy(&mutex)!=0)
    {
        perror("Blad funkcji pthred_mutex_destroy");
        exit(EXIT_FAILURE);
    }
    return 0;
}