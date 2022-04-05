#ifndef SEM_H
#define SEM_H

#include <semaphore.h>

sem_t* sem_creat(char*, int, mode_t, unsigned int);
sem_t* sem_open_(const char*, int);
int sem_getval(sem_t*, int*);
void sem_action(sem_t*, int);
void sem_close_(sem_t*);
void sem_unlink_(const char*);

#endif