#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int main(int argc,char * argv[])
{
	int fd;
	FILE* file;
	char*s =(char*)"hello world\n";
	if((fd=open("test1.txt",O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR))==-1)
	{
		cout<<"error open file"<<endl;
		return -1;
	}
	
	if((file=fopen("test2.txt","w+"))==NULL)
	{
		cout<<"error open file"<<endl;
		return -1;
	}

	cout<<"file has been opened"<<endl;

	sleep(15);

	if(write(fd,s,strlen(s))<strlen(s))
	{
		cout<<"write error"<<endl;
		return -1;
	}

	if(fwrite(s,sizeof(char),strlen(s),file)<strlen(s))
	{
		cout<<"write error in 2"<<endl;
		return -1;
	}
	cout<<"After write"<<endl;
	sleep(15);
	cout<<"After sleep"<<endl;
	close(fd);
	return 0;
}
