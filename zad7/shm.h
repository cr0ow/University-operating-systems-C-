#ifndef SHM_H
#define SHM_H

#include <fcntl.h>
#define NELE 45
#define NBUF 5

struct Towar
{
    char* buf;
}towar;

typedef struct
{
    int wstaw, wyjmij;
    char buf[NBUF][NELE];   
} SegmentPD;

int _open(const char *, int, mode_t);
void _length(int, off_t);
void _close(int);
void _unlink(const char *);
void* _map(void *, size_t, int, int, int, off_t);
void _munmap(void *, size_t);

#endif