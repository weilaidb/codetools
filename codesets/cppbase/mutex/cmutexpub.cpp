#include "cmutexpub.h"
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

pthread_mutex_t cmutexpub::m_mutex = PTHREAD_MUTEX_INITIALIZER;
unsigned int cmutexpub::global_count = 0;
pthread_cond_t cmutexpub::m_cond;

pid_t gettid(void)
{
    return syscall(SYS_gettid);
}

cmutexpub::cmutexpub()
{

}

void *cmutexpub::print_msg1(void *arg)
{
    int i=0;
    //    for(i=0;i<loopcnt;i++){
    while(1){
        //        pthread_mutex_lock(&m_mutex);
        while(EOWNERDEAD==pthread_mutex_lock(&m_mutex)) {
            pthread_mutex_consistent(&m_mutex);
            pthread_mutex_unlock(&m_mutex);
        }
        global_count++;


        printf("output : %d:%#x\n",i++, gettid());
        usleep(1);
        pthread_cond_signal(&m_cond);
        pthread_mutex_unlock(&m_mutex);


//        pthread_mutex_unlock(&m_mutex);
//        while(EOWNERDEAD==pthread_mutex_lock(&mutex)) {
//        pthread_mutex_consistent(&mutex);
//        pthread_mutex_unlock(&mutex);
//        }
//        while(global_count<=0) {
//        pthread_cond_wait(&cond, &mutex);
//        }
//        global_count--;
//        pthread_mutex_unlock(&mutex);

    }
}

void *cmutexpub::print_msg2(void *arg)
{
    int i=0;
    //    for(i=0;i<loopcnt;i++){
    while(1){
        //        pthread_mutex_lock(&m_mutex);
        printf("output : %d:%#x\n",i++, gettid());
        usleep(1);
        pthread_mutex_unlock(&m_mutex);
    }
}

void *cmutexpub::print_msg3(void *arg)
{
    int i=0;
    //    for(i=0;i<loopcnt;i++){
    while(1){
        //        pthread_mutex_lock(&m_mutex);
        printf("output : %d:%#x\n",i++, gettid());
        usleep(1);
        pthread_mutex_unlock(&m_mutex);
    }
}

void *cmutexpub::print_msg4(void *arg)
{
    int i=0;
    //    for(i=0;i<loopcnt;i++){
    while(1){
        //        pthread_mutex_lock(&m_mutex);
        printf("output : %d:%#x\n",i++, gettid());
        usleep(1);
        pthread_mutex_unlock(&m_mutex);
    }
}

void *cmutexpub::print_msg5(void *arg)
{
    int i=0;
    //    for(i=0;i<loopcnt;i++){
    while(1){
        //        pthread_mutex_lock(&m_mutex);
        printf("output : %d:%#x\n",i++, gettid());
        usleep(1);
        pthread_mutex_unlock(&m_mutex);
    }
}

void *cmutexpub::print_msg6(void *arg)
{
    int i=0;
    //    for(i=0;i<loopcnt;i++){
    while(1){
        //        pthread_mutex_lock(&m_mutex);
        printf("output : %d:%#x\n",i++, gettid());
        usleep(1);
        pthread_mutex_unlock(&m_mutex);
    }
}


int cmutexpub::createtask()
{
    pthread_t id1;
    pthread_t id2;
    pthread_mutexattr_t mutexattr;
    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_setrobust(&mutexattr, PTHREAD_MUTEX_ROBUST);
    pthread_mutex_init(&m_mutex,&mutexattr);
    pthread_create(&id1,nullptr,print_msg1,nullptr);
    pthread_create(&id2,nullptr,print_msg2,nullptr);
    pthread_create(&id2,nullptr,print_msg3,nullptr);
    pthread_create(&id2,nullptr,print_msg4,nullptr);
    pthread_create(&id2,nullptr,print_msg5,nullptr);
    pthread_create(&id2,nullptr,print_msg6,nullptr);
    //    pthread_create(&id2,nullptr,print_msg,nullptr);

    pthread_join(id1,nullptr);
    pthread_join(id2,nullptr);
    pthread_mutex_destroy(&m_mutex);
    return 0;
}

#if 1
int main(int argc, char *argv[])
{
    cmutexpub::createtask();
    return 0;
}
#endif

