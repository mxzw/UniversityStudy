#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define PTHREADNUM 2

void* Mypthreadcallback(void* arg)
{
    printf("i am work thread\n"); 
    while(1)
    {
        sleep(1);
    }
     pthread_cancel(pthread_self());
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

    puts("pthread_join test start!!");
    void *retval;
    ret = pthread_join(tid,&retval);
    if(ret < 0)
    {
        perror("pthread_join");
        return 0;
    }

    printf("pthread_join success!,It's retval is %p\n",retval);

    while(1){
        puts("i am main thread");
        sleep(1);
    }

    return 0;
}
