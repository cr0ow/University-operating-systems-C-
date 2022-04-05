#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    printf("Proces macierzysty:\n");
    printf("UID:  %d\n",getuid());
    printf("GID:  %d\n",getgid());
    printf("PID:  %d\n",getpid());
    printf("PPID: %d\n",getppid());
    printf("PGID: %d\n\n",getpgid(0));
    printf("Procesy potomne:\n\n");

    for(int i=0; i<3; i++)
    {
        switch(fork())
        {
            case -1:
            {
                perror("fork error\n");
                exit(1);
            }
            case 0:
            {
                printf("UID:  %d\n",getuid());
                printf("GID:  %d\n",getgid());
                printf("PID:  %d\n",getpid());
                printf("PPID: %d\n",getppid());
                printf("PGID: %d\n\n",getpgid(0));
                sleep(10);
                break;
            }
            default:
            {
                sleep(1);
                break;
            }
        }
    }
    return 0;
}