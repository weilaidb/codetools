#include "csempub.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/syscall.h> /* must include this file */

csempub::csempub()
{

}

#include<stdio.h>
#include<stdlib.h>

#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "basetypepub.h"

#define MAXSIZE 1000000

WORD64 stack[MAXSIZE];

WORD64 size =0;
sem_t sem;

void *privide_data(void *arg)
{
    WORD64 i;
    for(i =0;i<MAXSIZE;++i)
    {
        stack[i] = i;
        sem_post(&sem);
    }
}

void *handle_data(void *arg)
{
    WORD64 i;
    while((i = size ++) <MAXSIZE)
    {
        sem_wait(&sem);
        printf("cross : %llu X %llu = %llu \n",stack[i],stack[i],stack[i] * stack[i]);
        //    sleep(1);
    }
}

int main()
{
    pthread_t privider,handler;
    sem_init(&sem,0,0);
    pthread_create(&privider,NULL,privide_data,NULL);
    pthread_create(&handler,NULL,handle_data,NULL);
    pthread_join(privider,NULL);
    pthread_join(handler,NULL);
    sem_destroy(&sem);

    return 0;
}
