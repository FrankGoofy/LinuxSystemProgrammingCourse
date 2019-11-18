#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>

int main()
{
	pid_t pid;
	int k,status;
	pid=fork();
	if(pid<0)
	{
		perror("fork failed!\n");
		return -1;
	}
	else if(pid==0)
	{
		printf("child %d : running!\n",getpid());
		while(1);
		exit(120);
	}
	else
	{
		if((k=wait(&status))!=0)
		{
			if(WIFEXITED(status))
			{
				printf("child exit with exit!\n exit code = %d\n",WEXITSTATUS(status));
			}
			else if(WIFSIGNALED(status))
			{
				printf("child terminated with signal!\n signal number = %d \n",WTERMSIG(status));
			}
		}
	}
}
