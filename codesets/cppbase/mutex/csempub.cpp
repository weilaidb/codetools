#include "csempub.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/syscall.h>

#include "basetypepub.h"

#define NULL nullptr

csempub::csempub()
{

}


#define MAXSIZE 10

volatile unsigned int global_count = 0;
sem_t sem;

static pid_t gettid(void)
{
    return syscall(SYS_gettid);
}


void *privide_data(void *arg)
{
    WORD64 i = 0;
    while (1) {
        sem_wait(&sem);
        global_count++;
        printf("output : %-4llu, cnt:%-5u :%#x\n",i++, global_count, gettid());
        sem_post(&sem);
    }
}

void *handle_data(void *arg)
{
    WORD64 i = 0;
    while (1) {
        sem_wait(&sem);
        global_count++;
        printf("output : %-4llu, cnt:%-5u :%#x\n",i++, global_count, gettid());
        sem_post(&sem);
    }
}

#if 1
int main()
{
    pthread_t privider,handler;
    sem_init(&sem,0,1);
    pthread_create(&handler,NULL,handle_data,NULL);
    pthread_create(&privider,NULL,privide_data,NULL);
    pthread_join(privider,NULL);
    pthread_join(handler,NULL);
    sem_destroy(&sem);

    return 0;
}
#endif
