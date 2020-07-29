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
    static void *print_msg3(void *arg);
    static void *print_msg4(void *arg);
    static void *print_msg5(void *arg);
    static void *print_msg6(void *arg);
private:
    static pthread_mutex_t m_mutex;
};

#endif // CMUTEXPUB_H
