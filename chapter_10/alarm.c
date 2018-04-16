#include "apue.h"
#include<pwd.h>
#include<signal.h>
#include<unistd.h>

static void my_alarm(int singno)
{
    struct passwd *rootptr;
    printf("in signal handler\n");
    if((rootptr = getpwnam("root")) == NULL)
        err_sys("getpwnam(root) error");
    alarm(1);
}

int main()
{
    struct passwd *ptr;
    signal(SIGALRM, my_alarm);
    alarm(1);
    for( ; ; )
    {
        if((ptr = getpwnam("sll")) == NULL)
            err_sys("getpwnam");
        if(strcmp("sll", ptr->pw_name) != 0)
            printf("return value corrupted!, pw_name: %s\n", ptr->pw_name);
    }
    return 0;
}




