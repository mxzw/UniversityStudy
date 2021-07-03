#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define PTHREADNUM 2

void* Mypthreadcallback(void* arg)
{
    while(1)
    {
        printf("i am work thread\n"); 
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid;

    int ret = pthread_create(&tid,NULL,Mypthreadcallback,NULL);
    if(ret < 0)
    {
        perror("pthread_create");
        return 0;
    }
    puts("pthread_cancel test start!!");
    puts("It's test to cancel main thread");
    ret = pthread_cancel(pthread_self());
    if(ret < 0)
    {
        perror("pthread_cancel");
        return 0;
    }

    while(1){
        sleep(1);
    }

    return 0;
}
