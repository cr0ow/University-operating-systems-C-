#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    printf("UID:  %s\n",argv[1]);
    printf("GID:  %s\n",argv[2]);
    printf("PID:  %s\n",argv[3]);
    printf("PPID: %s\n",argv[4]);
    printf("PGID: %s\n\n",argv[5]);
    return 0;
}