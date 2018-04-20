#include "apue.h"
#include<pthread.h>
#include<unistd.h>
#include<sys/time.h>
#include<limits.h>
#include<assert.h>

#define NUM 1000000
#define THREAD 4
int origin_arr[4*NUM+1];
int sort_arr[4*NUM+1];
int thread_arr[4*NUM+1];
int normal_arr[4*NUM+1];

static pthread_barrier_t barrier;


void init()
{
    int n = NUM*THREAD, i;
    srand(time(0));
    for(i = 0; i < n; i++)
        origin_arr[i] = rand();
    pthread_barrier_init(&barrier, NULL, THREAD+1);
}


int cmp(const void *a, const void *b)
{
    return *(int*)a < *(int*)b ? -1 : 1;
}

double normal_time()
{
    int i;
    for(i = 0; i < NUM*THREAD; i++)
        normal_arr[i] = origin_arr[i];
    struct timeval s, e;
    gettimeofday(&s, NULL);
    qsort(normal_arr, NUM*THREAD, sizeof(int), cmp);
    gettimeofday(&e, NULL);
    return 1.0*(e.tv_sec*1000000 + e.tv_usec - s.tv_sec*1000000 - s.tv_usec) / 1000000.0;
}


void* thr_fn(void *arg)
{
    long s = (long)arg;
    qsort(thread_arr+s, NUM, sizeof(int), cmp);
    pthread_barrier_wait(&barrier);
    return (void*)0;
}



void merg()
{
    int num[THREAD], i;
    for(i = 0; i < THREAD; i++) num[i] = i*NUM;
    int cnt = 0;
    for( ; ; )
    {
        int k, mi = INT_MAX;
        for(i = 0; i < THREAD; i++)
        {
            if(num[i] < (i+1)*NUM && thread_arr[num[i]] < mi)
            {
                mi = thread_arr[num[i]];
                k = i;
            }
        }
        if(mi == INT_MAX) break;
        sort_arr[cnt++] = mi;
        num[k]++;
    }
}

double thread_time()
{
    pthread_t tid[THREAD];
    long i;
    for(i = 0; i < NUM*THREAD; i++)
        thread_arr[i] = origin_arr[i];
    struct timeval s, e;
    gettimeofday(&s, NULL);
    for(i = 0; i < THREAD; i++)
    {
        if(pthread_create(&tid[i], NULL, thr_fn, (void*)(i*NUM)) != 0)
            err_sys("pthread_create");
    }
    pthread_barrier_wait(&barrier);
    merg();
    gettimeofday(&e, NULL);
    return 1.0*(e.tv_sec*1000000 + e.tv_usec - s.tv_sec*1000000 - s.tv_usec) / 1000000.0;
}


void check()
{
    int i;
    for(i = 0; i < THREAD*NUM; i++)
        assert(normal_arr[i] == sort_arr[i]);
}

int main()
{
    init();
    printf("thread time: %.2fs\n", thread_time());
    printf("normal_time: %.2fs\n", normal_time());
    check();
    return 0;
}

