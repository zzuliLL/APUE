#include "apue.h"
#include<time.h>

int main()
{
    time_t t;
    if(time(&t) < 0)
        err_sys("time");
    struct tm* tmp = localtime(&t);
    if(tmp == NULL)
        err_sys("localtime");
    char buf[128];
    if(strftime(buf, sizeof(buf), "%r, %a %b %d, %Y", tmp) == 0)
        err_sys("strftime");
    printf("time: %s\n", buf);
    return 0;
}

