#include "apue.h"
#include<pthread.h>
#include<unistd.h>


void cleanup(void *msg)
{
    puts(msg);
}


void* thr_fn1(void *arg)
{

    printf("thread1 start\n");
    pthread_cleanup_push(cleanup, "thread1 first");
    pthread_cleanup_push(cleanup, "thread1 seconed");
    puts("thread1 end");
    if(arg)
    {
        return (void*)1;
    }
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    return (void*)0;
}


void* thr_fn2(void *arg)
{

    printf("thread2 start\n");
    pthread_cleanup_push(cleanup, "thread2 first");
    pthread_cleanup_push(cleanup, "thread2 seconed");
    puts("thread2 end");
    if(arg)
    {
        pthread_exit((void*)2);
    }
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit((void*)2);
}

int main()
{
    pthread_t tid1, tid2;
    if(pthread_create(&tid1, NULL, thr_fn1, (void*)1) != 0)
        err_sys("pthread_create1");

    if(pthread_create(&tid2, NULL, thr_fn2, (void*)2) != 0)
        err_sys("pthread_create1");
    void *status;
    if(pthread_join(tid1, &status) != 0)
        err_sys("pthread_join");
    printf("return from thread1 %ld\n", (long)status);

    if(pthread_join(tid2, &status) != 0)
        err_sys("pthread_join");
    printf("return from thread2 %ld\n", (long)status);

    return 0;
}

