#include "apue.h"
#include<time.h>
#include<limits.h>
#include<unistd.h>

static unsigned long long g_val = 0ll;
static int nzero;

void print(char *who)
{
    printf("%s : %lld\n", who, g_val);
}


int main(int argc, char *argv[])
{
    int inc = 0;
    int n_value;
    char *who;
    if(argc >= 2)
    {
        inc = atoi(argv[1]);
    }
    nzero = sysconf(_SC_NZERO);
    pid_t pid = fork();

    if(pid < 0)
        err_sys("fork");
    else if(pid == 0)
    {
        who = "child";
        n_value = nice(inc) + nzero;
        if(n_value < 0 && errno != 0)
            err_sys("child nice");
        printf("child nice value: %d\n", n_value);
    }
    else
    {
        who = "parent";
        n_value = nice(0) + nzero;
        if(n_value < 0 && errno != 0)
            err_sys("parent nice");
        printf("parent nice value: %d\n", n_value);
    }
    time_t s, e;
    if(time(&s) < 0) err_sys("time");
    while(1)
    {
        g_val++;
        if(time(&e) < 0) err_sys("time");
        if(e - s >= 10)
        {
            print(who);
            exit(0);
        }

    }
    return 0;

}

