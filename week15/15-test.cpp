#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define	MAXNITEMS 		10      //缓冲区大小为10
/*
	两个生产者，实现它们之间的同步  
	缓冲区内第一个位置放1，第二个位置放2这种
	一个消费者，检验其是否出错
	生产者消费者一起创建 还要保证生产者和消费者之间的同步
	还要防止再期待的条件尚未达到的时候不断轮询造成资源浪费，所以要有信号量
*/

int buff[MAXNITEMS];


struct 
{
	pthread_mutex_t lock;
	int key;
	int value;
}put = {
	PTHREAD_MUTEX_INITIALIZER
};

//通过信号量来控制消息的传递  每一个信号量关联着一个互斥锁
struct {

	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int nready;
} nready = {
	PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER
};

//这样对结构体初始化

//都要加上shared前缀，不要忘了！！！
//还忘记写循环了，没有循环放元素

void * create_producer1()
{
	for(;;)
	{
		pthread_mutex_lock(&put.lock);
		if(put.key >= MAXNITEMS)
		{
			pthread_mutex_unlock(&put.lock);//这里为shared.lock还要加&符号
			printf("producer1: my function is over~\n"); 
			pthread_exit(NULL);

		}
		buff[put.key] = put.value;
		printf("producer1 have put the data: %d\n",put.value);
		put.key ++;
		put.value ++;
		pthread_mutex_unlock(&put.lock);

		pthread_mutex_lock(&nready.mutex);
		if(nready.nready == 0)
			pthread_cond_signal(&nready.cond);
		nready.nready++;
		pthread_mutex_unlock(&nready.mutex);

	}

}


void * create_producer2()
{

	for(;;)
	{
		pthread_mutex_lock(&put.lock);
		if(put.key >= MAXNITEMS)
		{
			pthread_mutex_unlock(&put.lock);//这里为shared.lock还要加&符号
			printf("producer2: my function is over~\n"); 
			pthread_exit(NULL);

		}
		buff[put.key] = put.value;
		printf("producer2 have put the data: %d\n",put.value);
		put.key ++;
		put.value ++;
		pthread_mutex_unlock(&put.lock);

		pthread_mutex_lock(&nready.mutex);
		if(nready.nready == 0)
			pthread_cond_signal(&nready.cond);
		nready.nready++;
		pthread_mutex_unlock(&nready.mutex);

	}
}


void * create_consumer()
{

	for(int i = 0;i < 10;i++)
	{
		pthread_mutex_lock(&nready.mutex);
		while(nready.nready == 0)
				pthread_cond_wait(&nready.cond,&nready.mutex);
		nready.nready -- ;

		pthread_mutex_unlock(&nready.mutex);
		
		if(buff[i] != i)
		{
			printf("buff[%d] = %d was wrong!\n", i ,buff[i]);
			
		}
	}


	printf("All have scanned!\n");
	return (NULL);
}



int main(int argc, char *argv[])
{
	pthread_t tid1,tid2;
	pthread_t consumer_tid;



	printf("I will create two producers and one consumers\n");

	if(pthread_create(&tid1,NULL,(void* (*)(void*))create_producer1,NULL) != 0)
		printf("create producer1 failed!\n");
	else
		printf("producer1 has been create!\n");



	if(pthread_create(&tid2,NULL,(void* (*)(void*))create_producer2,NULL) != 0)
		printf("create producer2 failed!\n");
	else
		printf("producer2 has been create!\n");


	if(pthread_create(&consumer_tid,NULL,(void* (*)(void*))create_consumer,NULL) != 0)
		printf("create consumer failed!\n");
	else
		printf("consumer has been create and begin check out the buff...\n");


//怎样等待线程结束呢。好像就直接这样接着写结束
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	pthread_join(consumer_tid,NULL);


	return 0;
}
