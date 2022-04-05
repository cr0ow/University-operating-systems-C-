#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mqueue.h>

mqd_t create(const char* name_, int flag, mode_t mode, struct mq_attr *attr)
{
    mqd_t des=mq_open(name_, flag, mode, attr);
    if(des==(mqd_t)-1)
    {
        perror("Blad funkcji    mq_open");
        exit(EXIT_FAILURE);
    }
    return des;
}

mqd_t mqopen(const char* name_, int flag)
{
    mqd_t des=mq_open(name_, flag);
    if(des==(mqd_t)-1)
    {
        perror("Blad funkcji mq_open");
        exit(EXIT_FAILURE);
    }
    return des;
}

void mqclose(mqd_t mqdes)
{
    if(mq_close(mqdes)==-1)
    {
        perror("Blad funkcji mq_close");
        exit(EXIT_FAILURE);
    }
}

void mqunlink(const char* name_)
{
    if(mq_unlink(name_)==-1)
    {
        perror("Blad funkcji mq_unlink");
        exit(EXIT_FAILURE);
    }
}

int getattr(mqd_t mqdes, struct mq_attr *attr)
{
    int g=mq_getattr(mqdes,attr);
    if(g==-1)
    {
        perror("Blad funkcji mq_getattr");
        exit(EXIT_FAILURE);
    }
    return g;
}

int setattr(mqd_t mqdes, struct mq_attr *newattr, struct mq_attr *oldattr)
{
    int s=mq_setattr(mqdes, newattr, oldattr);
    if(s==-1)
    {
        perror("Blad funkcji mq_setattr");
        exit(EXIT_FAILURE);
    }
}

void send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio)
{
    if(mq_send(mqdes, msg_ptr, msg_len, msg_prio)==-1)
    {
        perror("Blad funkcji mq_send");
        exit(EXIT_FAILURE);
    }
}

void receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int* msg_prio)
{
    if(mq_receive(mqdes, msg_ptr, msg_len, msg_prio)==-1)
    {
        perror("Blad funkcji mq_send");
        exit(EXIT_FAILURE);
    }
}