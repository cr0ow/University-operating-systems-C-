#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

sem_t* sem_creat(char *name, int flag, mode_t mode, unsigned int val)
{
    sem_t* sem=sem_open(name,flag,mode,val);
    if(sem==SEM_FAILED)
    {
        perror("Blad funkcji sem_open");
        exit(EXIT_FAILURE);
    }
    return sem;
}

sem_t* sem_open_(const char *name, int flag)
{
    sem_t* sem = sem_open(name,flag);
    if(sem==SEM_FAILED)
    {
        perror("Blad funkcji sem_open");
        exit(EXIT_FAILURE);
    }
    return sem;
}

int sem_getval(sem_t *sem, int *val)
{
    if(sem_getvalue(sem,val)==-1)
    {
        perror("Blad funkcji sem_getvalue");
        exit(EXIT_FAILURE);
    }
    return *val;
}

void sem_action(sem_t *sem, int action)
{
    if(action==1)
    {
        if(sem_post(sem)==-1)
        {
            perror("Blad funkcji sem_post");
            exit(EXIT_FAILURE);
        }
    }
    else if(action==2)
    {
        if(sem_wait(sem)==-1)
        {
            perror("Blad funkcji sem_wait");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        perror("Niepoprawny argument wywolania funckji sem_action");
        exit(EXIT_FAILURE);
    }
}

void sem_close_(sem_t *sem)
{
    if(sem_close(sem)==-1)
    {
        perror("Blad funkcji sem_close");
        exit(EXIT_FAILURE);
    }
}

void sem_unlink_(const char *name)
{
    if(sem_unlink(name)==-1)
    {
        perror("Blad funkcji sem_unlink");
        exit(EXIT_FAILURE);
    }
}