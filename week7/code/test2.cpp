#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc,char* argv[])
{
	int i=0;
	for(i=0;i<0x256;i++){printf("a");}
	while(1);
}
