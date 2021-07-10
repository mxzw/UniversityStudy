#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREADNUM 2

int ticket = 100000;

void* threadEntry(void* arg)
{
    while(1)
    {
        if(ticket > 0)
        {
            printf("i am Thread %p, i have tecket ID is %d\n",pthread_self(),ticket);
            --ticket;
        }
        else
        {
            pthread_exit(NULL);
        }
    }
    return NULL;
}

int main()
{
    pthread_t tid[THREADNUM];

    for(int i = 0; i < THREADNUM; ++i)
    {
        int ret = pthread_create(&tid[i],NULL,threadEntry,NULL);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
    }

    for(int i = 0;i < THREADNUM; ++i)
    {
        int ret = pthread_join(tid[i],NULL);
        if(ret < 0)
        {
            perror("pthread_join");
            return 0;
        }
    }

    puts("thread join end.....");
    return 0;
}
