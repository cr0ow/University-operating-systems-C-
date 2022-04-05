#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int _open(const char *name, int flags, mode_t mode)
{
    int des=shm_open(name,flags,mode);
    if(des==-1)
    {
        perror("Blad funkcji shm_open");
        exit(EXIT_FAILURE);
    }
    return des;
}

void _length(int des, off_t length)
{
    if(ftruncate(des,length)==-1)
    {
        perror("Blad funkcji ftruncate");
        exit(EXIT_FAILURE);
    }
}

void _close(int des)
{
    if(close(des)==-1)
    {
        perror("Blad funkcji close");
        exit(EXIT_FAILURE);
    }
}

void _unlink(const char *name)
{
    if(shm_unlink(name)==-1)
    {
        perror("Blad funkcji shm_unlink");
        exit(EXIT_FAILURE);
    }
}

void* _map(void *addr, size_t length, int prot, int flags, int des, off_t offset)
{
    void *p=mmap(addr,length,prot,flags,des,offset);
    if(p==MAP_FAILED)
    {
        perror("Blad funkcji mmap");
        exit(EXIT_FAILURE);
    }
    return p;
}

void _munmap(void *addr, size_t length)
{
    if(munmap(addr,length)==-1)
    {
        perror("Blad funkcji munmap");
        exit(EXIT_FAILURE);
    }
}