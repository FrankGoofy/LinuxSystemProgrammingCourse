#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int ret;
    printf("caller1:pid=%d,ppid=%d\n", getpid(), getppid());
    execl("home/rlk/test1", "./test1", "123", "456", NULL);
    printf("After calling!\n");
    sleep(1);
    return 0;
}
