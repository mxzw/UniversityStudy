#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define PTHREADNUM 2

void* Mypthreadcallback(void* arg)
{
    int* tmp = (int*)arg;
    puts("pthread_exit test!!");
    //pthread_exit(NULL);
    //pthread_cancel(pthread_self());
    while(1)
    {
        printf("i am work thread ,my thread is %d\n",*tmp); 
        sleep(3);
    }
    delete tmp;
    return NULL;
}

int main()
{
    pthread_t tid[PTHREADNUM];

    for(int i = 0; i < PTHREADNUM;++i)
    {
        int* tmp = new int(i+1);
        int ret = pthread_create(&tid[i],NULL,Mypthreadcallback,tmp);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
    }
    puts("pthread_cancel test start!!");
    puts("It's test to cancel work thread 1");
    int ret = pthread_cancel(tid[0]);
    if(ret < 0)
    {
        perror("pthread_cancel");
        return 0;
    }
    sleep(2);
    puts("It's test to cancel work thread 2");
    ret = pthread_cancel(tid[1]);
    if(ret < 0)
    {
        perror("pthread_cancel");
        return 0;
    }
    while(1){

        puts("i am main thread");
        sleep(1);
    }

    return 0;
}
