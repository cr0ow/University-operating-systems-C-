#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv)
{
    int* p;
    char *pre = malloc(2 * sizeof(char));
    char *nazwa = malloc((sizeof *argv[1]/sizeof argv[1]) * sizeof(char));
    strcpy(pre,"./");
    strcpy(nazwa,argv[1]);
    char *plik = strcat(pre,nazwa);
    char uid[10], gid[10], pid[10], ppid[10], pgid[10];

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
                perror("fork error\n");
                exit(1);
            case 0:
                sprintf(uid,"%d",getuid());
                sprintf(gid,"%d",getgid());
                sprintf(pid,"%d",getpid());
                sprintf(ppid,"%d",getppid());
                sprintf(pgid,"%d",getpgid(0));
                execl(plik, argv[1], uid, gid, pid, ppid, pgid, NULL);
                perror("execl error");
                _exit(2);
            default:
                wait(p);
                break;
        }
    }
    free(pre);
    free(nazwa);
    return 0;
}