#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
int t = 0;
sem_t empty, full;
pthread_mutex_t mutex;
void *producer(void *arg)
{
    int *time = (int *)arg;
    while (true)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        //add
        t=t+5;
        printf("producer add 5 to %d\n", t);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(*time);
    }
}

void *customer(void *arg)
{

    while (true)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        //delete
        t=t-5;
        printf("customer delete 5 to %d\n", t);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        //sleep(2);
    }
}

int main()
{
    pthread_t pthread_producer, pthread_producer_2;
    pthread_t pthread_customer;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 5);
    int a = 1;
    int b = 1;
    pthread_create(&pthread_producer, NULL, producer, &a);
    //pthread_create(&pthread_producer_2, NULL, producer, &b);
    pthread_create(&pthread_customer, NULL, customer, NULL);
    pthread_join(pthread_customer, NULL);
    pthread_join(pthread_producer, NULL);
    //pthread_join(pthread_producer_2, NULL);
    return 0;
}
