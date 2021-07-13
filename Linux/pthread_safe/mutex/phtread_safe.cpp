#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREADNUM 2

int ticket = 10;
//注意互斥锁变量的定义一定要在全局中定义
pthread_mutex_t mutex;

void* threadEntry(void* arg)
{
    while(1)
    {
        //在对临界资源进行操作之前进行加锁
        pthread_mutex_lock(&mutex);
        if(ticket > 0)
        {
            printf("i am Thread %p, i have tecket ID is %d\n",pthread_self(),ticket);
            --ticket;
        }
        else
        {
            //注意一定要在线程所有可能退出的位置进行解锁
            //如果在该位置不解锁，那么就有可能该工作线程带着这把锁退出了，
            //而其他线程会一直处于等待拿锁的时刻，这样就造成了死锁
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t tid[THREADNUM];
    //在工作线程之前动态的创建互斥锁
    pthread_mutex_init(&mutex,NULL);

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

    //在所有线程都退出之后释放互斥锁
    pthread_mutex_destroy(&mutex);

    puts("thread join end.....");
    return 0;
}
