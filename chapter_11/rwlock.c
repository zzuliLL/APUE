#include "apue.h"
#include<pthread.h>
#include<unistd.h>

struct job
{
    struct job *pre, *nx;
    pthread_t tid;
};


struct queue
{
    struct job *head, *tail;
    pthread_rwlock_t lock;
};

int queue_init(struct queue *qp)
{
    qp->head = qp->tail = NULL;
    int err = pthread_rwlock_init(&qp->lock, NULL);
    if(err) return err;
    return 0;
}

void job_insert(struct queue *qp, struct job *jp)
{
    pthread_rwlock_wrlock(&qp->lock);
    if(qp->head == NULL)
    {
        jp->nx = jp->pre = NULL;
        qp->head = qp->tail = jp;
    }
    else
    {
        jp->nx = qp->head;
        qp->head->pre = jp;
        jp->pre = NULL;
        qp->head = jp;
    }
    pthread_rwlock_unlock(&qp->lock);
}

void job_append(struct queue *qp, struct job *jp)
{
    pthread_rwlock_wrlock(&qp->lock);
    if(qp->head == NULL)
    {
        jp->nx = jp->pre = NULL;
        qp->head = qp->tail = jp;
    }
    else
    {
        jp->nx = NULL;
        jp->pre = qp->tail;
        qp->tail->nx = jp;
        qp->tail = jp;

    }
    pthread_rwlock_unlock(&qp->lock);
}



void job_remove(struct queue *qp, struct job *jp)
{
    pthread_rwlock_wrlock(&qp->lock);
    if(qp->head == jp && qp->tail == jp)
    {
        qp->head = qp->tail = NULL;
    }
    else if(qp->head == jp)
    {
        qp->head->nx->pre = NULL;
        qp->head = qp->head->nx;
    }
    else
    {
        jp->pre->nx = jp->nx;
        jp->nx->pre = jp->pre;
    }
    free(jp);
    pthread_rwlock_unlock(&qp->lock);
}


struct job* job_find(struct queue *qp, pthread_t tid)
{
    struct job *jp;
    if(pthread_rwlock_rdlock(&qp->lock) != 0)
        return NULL;
    for(jp = qp->head; jp != qp->tail; jp = jp->nx)
    {
        if(pthread_equal(tid, jp->tid))
            break;
    }
    pthread_rwlock_unlock(&qp->lock);
    return jp;
}


int main()
{
    return 0;
}












