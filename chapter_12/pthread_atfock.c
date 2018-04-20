#include "apue.h"
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void prepare()
{
    puts("prepare: lock1 lock2");
    pthread_mutex_lock(&lock1);
    pthread_mutex_lock(&lock2);
}

void child()
{
    puts("child unlock");
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
}

void parent()
{
    puts("parent unlock");
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
}

int main()
{
    pthread_atfork(prepare, parent, child);
    puts("starting to fork");
    if(fork() == 0) puts("child");
    else puts("parent");
    return 0;
}

