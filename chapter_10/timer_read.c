#include "apue.h"
#include<signal.h>
#include<setjmp.h>
#include<unistd.h>


jmp_buf buf;

void sig_alrm(int signo)
{
    longjmp(buf, 1);
}


int main()
{
    if(signal(SIGALRM, sig_alrm) == SIG_ERR)
        err_sys("signal");
    if(setjmp(buf))
    {
        err_sys("read error");
    }

    alarm(10);
    int x;
    scanf("%d", &x);
    alarm(0);
    printf("%d\n", x);
    return 0;
}

