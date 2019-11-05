#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <wait.h>
#include <fcntl.h>
#include <sys/stat.h>

#define INFILE "./in.txt"
#define OUTFILE "./out.txt"

int main()
{
    int fd1,fd2;
    char buf[1024];
    memset(buf,0,1024);
    fd1=open(INFILE,O_RDONLY);
    if (fd1<0)
    {
        fprintf(stderr,"failed to open %s, reason(%s)\n",INFILE,strerror(errno));
        return 1;
    }
    fd2=open(OUTFILE,O_WRONLY|O_CREAT|O_TRUNC,MODE);
    if (fd2<0)
    {
        fprintf(stderr,"failed to open %d,reason(%s)\n",OUTFILE,strerror(errno));
        return 1;
    }
    fork();
    while (read(fd1,buf,2)>0)
    {
        printf("%d:%s",getpid(),buf);
        sprintf();
    }
    return 0;
}