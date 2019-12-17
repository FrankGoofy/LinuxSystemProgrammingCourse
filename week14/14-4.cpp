#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 8
char *messages[NUM_THREADS];
struct thread_data
{
    int thread_id;
    int sum;
    char *message;
};

thread_data thread_data_array[NUM_THREADS];

void *PrintHello(void *threadarg)
{
    int taskid, sum;
    char *hello_msg;
    thread_data *my_data;
    sleep(1);
    my_data = (thread_data *)threadarg;
    taskid = my_data->message;
    printf("thread %d : %s sum = %d \n", taskid, hello_msg, sum);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int *taskids[NUM_THREADS];
    int rc, t, sum;
    sum = 0;
    messages[0] = "English: Hello World";
    messages[1] = "Franch: Bonjour, la mode" messages[3] = "Spanish: Hola";
    messages[4] = "messages 4 kanbuqing";
    messages[5] = "messages5 : kanbuqing1";
    messages[6] = "Japan :kanbuqing";
    messages[7] = "Latin : kanbuqing";

    for (t = 0; t < NUM_THREADS; t++)
    {
        sum = sum + t;
        thread_data_array[t].thread_id = t;
        thread_data_array[t].sum = sum;
        thread_data_array[t].message = messages[t];
        printf("creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello,
                            (void *)&thread_data_array[t]);
        if (rc)
        {
            printf("ERROR! return code f is %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
