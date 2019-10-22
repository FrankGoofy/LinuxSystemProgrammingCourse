#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global = 4;
int main(void)
{
	pid_t pid;
	int vari = 5;
	printf("before fork\n");
	if((pid = fork()) < 0)
	{
		printf("fork error\n");
		exit(0);
	}
	else if(pid == 0)
	{
		global++;
		vari--;
		printf("child changed\n");
	}
	else
	{
		printf("parent did not changed\n");
		printf("global = %d vari = %d\n",global,vari);
		exit(0);
	}
}
