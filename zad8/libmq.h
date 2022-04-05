#ifndef LIBMQ_H
#define LIBMQ_H

#include <sys/stat.h>
#include <mqueue.h>
#define name "/kolejka"

mqd_t create(const char*, int, mode_t, struct mq_attr*);
mqd_t mqopen(const char*, int);
void mqclose(mqd_t);
void mqunlink(const char*);
int getattr(mqd_t, struct mq_attr*);
int setattr(mqd_t, struct mq_attr*, struct mq_attr*);
void send(mqd_t, const char*, size_t, unsigned int);
void receive(mqd_t, char*, size_t, unsigned int*);

#endif