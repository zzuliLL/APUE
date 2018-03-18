#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include "apue.h"

#define BUF_SIZE 4096

static char fullpath[BUF_SIZE];
static int pos = 0;

static int total = 0;
static int regular = 0;
static int dir = 0;
static int symbol = 0;
static int charactor = 0;
static int block = 0;
static int socket = 0;
static int fifo = 0;

int myftw();
void counter(int mode);

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        err_sys("Usage: ./a.out <pathname>");
    }
    strcpy(fullpath, argv[1]);
    pos = strlen(fullpath);
    if(myftw() < 0)
    {
        exit(1);
    }
    printf("total file: %d\n", total);
    printf("regular file: %d %.2f%%\n", regular, 1.0*regular/total*100);
    printf("dirent file: %d %.2f%%\n", dir, 1.0*dir/total*100);
    printf("symbol file: %d %.2f%%\n", symbol, 1.0*symbol/total*100);
    printf("character fiel: %d %.2f%%\n", charactor, 1.0*charactor/total*100);
    printf("block file: %d %.2f%%\n", block, 1.0*block/total*100);
    printf("socket file: %d %.2f%%\n", socket, 1.0*socket/total*100);
    printf("fifo file: %d %.2f%%\n", fifo, 1.0*fifo/total*100);
    return 0;
}


int myftw()
{
    struct stat buf;
    if(stat(fullpath, &buf) == -1) err_sys("stat() error");
    counter(buf.st_mode);
    if(!S_ISDIR(buf.st_mode)) return 0;
    DIR *dire = opendir(fullpath);
    if(dire == NULL)
    {
        err_print(fullpath);
        err_sys("opendir() error");
    }
    struct dirent *dp;
    while(1)
    {
        dp = readdir(dire);
        if(dp == NULL) break;
        if(!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) continue;
        int len;
        len = pos = strlen(fullpath);
        fullpath[pos++] = '/';
        strcpy(&fullpath[pos], dp->d_name);
        if(myftw() < 0) return -1;
        fullpath[len] = '\0';
        pos = len;
    }
    closedir(dire);
    return 0;
}


void counter(int mode)
{
    ++total;
    switch(mode & S_IFMT)
    {
    case S_IFREG:
        ++regular;
        break;
    case S_IFDIR:
        ++dir;
        break;
    case S_IFBLK:
        ++block;
        break;
    case S_IFCHR:
        ++charactor;
        break;
    case S_IFLNK:
        ++symbol;
        break;
    case S_IFSOCK:
        ++socket;
        break;
    case S_IFIFO:
        ++fifo;
        break;
    default:
        err_exit("error file type");
    }
}


