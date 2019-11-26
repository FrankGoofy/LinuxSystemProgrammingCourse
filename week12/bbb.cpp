#include "my.h"

#define MSG "OMG, I CATCH THE SIGNAL SIGINT\n"
#define MSG_END "OH, FINISHED PROCESS SIGNAL SIGINT\n"

int do_heavy_work()
{
    int i;
    int k;
    srand(time(NULL));
    for ( i = 0; i < 1000000000; i++)
    {
        k=rand()%1234589;
    }
    return 0;
}

void signal_handler(int signo)
{
    write(2,MSG,strlen(MSG));
    do_heavy_work();
    write(2,MSG_END,strlen(MSG_END));
}

int main()
{
    char input[1024]={0};
    if (signal（SIGINT,signal_handler)==SIG_ERR)
    {
        fprintf(stderr,"signal failed!\n");
        return -1;
    }
    printf("input a string:\n");
    if (fgets(input,sizeof(input),stdin)==NULL)
    {
        fprintf(stderr,"fgets failed(%s)!\n",stderror(errno));
        return -2;
    }
    else
    {
        printf("you entered:%s",input);
    }
    
    return 0;
}