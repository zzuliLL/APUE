#include "apue.h"
#include<pthread.h>
#include<unistd.h>


void* thr_fn1(void *arg)
{
    printf("thread 1\n");
    return (void*)1;
}

void* thr_fn2(void *arg)
{
    printf("thread 2\n");
    return (void*)2;
}


int main()
{
    pthread_t tid1, tid2;
    if(pthread_create(&tid1, NULL, thr_fn1, NULL) != 0)
        err_sys("pthread_create1");
    if(pthread_create(&tid2, NULL, thr_fn2, NULL) != 0)
        err_sys("pthread_create2");
    void *status;
    if(pthread_join(tid1, &status) != 0)
        err_sys("pthread_join");
    printf("thread1: %ld\n", (long)status);
    if(pthread_join(tid2, &status) != 0)
        err_sys("pthread_join");
    printf("thread2: %ld\n", (long)status);
    return 0;
}

