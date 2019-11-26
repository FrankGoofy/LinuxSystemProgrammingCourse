#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
pid_t p;
int r;
int i;
for(i=0;i<3;i++)
{
	r = fork();
	if (r==0)
		break;
}

if(r==0 && i == 0)
{
printf("aaa");
}

if(r==0 && i == 1)
{
printf("bbb");
}

if(r==0 && i == 2)
{
printf("ccc");
}

return 0;

}
