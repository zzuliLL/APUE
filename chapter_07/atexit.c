#include "apue.h"


void my_exit1()
{
    puts("exit1");
}

void my_exit2()
{
    puts("exit2");
}

int main()
{
    if(atexit(my_exit2) != 0)
        err_sys("atexit");
    if(atexit(my_exit1) != 0)
        err_sys("atexit");
    if(atexit(my_exit1) != 0)
        err_sys("atexit");
    puts("main is done");
    return 9;
}

