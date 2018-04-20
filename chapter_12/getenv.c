#include "apue.h"
#include<pthread.h>
#include<unistd.h>

#define MAXSTRINGSZ 4096

pthread_once_t once = PTHREAD_ONCE_INIT;
pthread_key_t key;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

extern char **environ;

void create_once()
{
    pthread_key_create(&key, free);
}

char* get_env(char *name)
{
    pthread_once(&once, create_once);
    char *envbuf;
    pthread_mutex_lock(&mutex);
    envbuf = (char*)pthread_getspecific(key);
    if(envbuf == NULL)
    {
        envbuf = malloc(MAXSTRINGSZ);
        if(envbuf == NULL)
        {
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
        pthread_setspecific(key, envbuf);
    }

    int i, len = strlen(name);
    for(i = 0; environ[i] != NULL; i++)
    {
        if((strncmp(name, environ[i], len) == 0) && environ[i][len] == '=')
        {
            strncpy(envbuf, &environ[i][len], MAXSTRINGSZ-1);
            pthread_mutex_unlock(&mutex);
            return envbuf;
        }
    }
    pthread_mutex_unlock(&mutex);
    return NULL;

}


void* thr_fn(void *arg)
{
    char *v = get_env("PATH");
    puts(v);
    puts("");
    return NULL;
}

int main()
{
    int i;
    pthread_t tid;
    for(i = 0; i < 10; i++)
    {
        pthread_create(&tid, NULL, thr_fn, NULL);
    }
    pthread_join(tid, NULL);
    return 0;
}

