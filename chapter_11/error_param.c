#include "apue.h"
#include<pthread.h>
#include<unistd.h>



struct foo
{
    int a, b, c, d;
};


void pr_foo(struct foo *f, const char *msg)
{
    printf("%s a = %d, b = %d, c = %d, d = %d\n", msg, f->a, f->b, f->c, f->d);
}

void* thr_fn1(void *arg)
{
    struct foo f = {1, 2, 3, 4};
    pr_foo(&f, "thread: ");
    pthread_exit((void*)&f);
}


int main()
{
    pthread_t tid1;
    if(pthread_create(&tid1, NULL, thr_fn1, NULL) != 0)
        err_sys("pthread_create1");

    void *status;
    if(pthread_join(tid1, &status) != 0)
        err_sys("pthread_join");
    pr_foo((struct foo*)status, "main: ");
    return 0;
}

