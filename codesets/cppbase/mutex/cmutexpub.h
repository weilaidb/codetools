#ifndef CMUTEXPUB_H
#define CMUTEXPUB_H

#include <pthread.h>

class cmutexpub
{
public:
    cmutexpub();
    static int createtask();
    static void *print_msg1(void *arg);
    static void *print_msg2(void *arg);
private:
    static pthread_mutex_t m_mutex;
    static volatile unsigned int global_count;
    static pthread_cond_t m_cond;  //条件变量

};

#endif // CMUTEXPUB_H
