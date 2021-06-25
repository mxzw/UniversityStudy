#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void* pthreadEntry(void* arg)
{
    int* t = (int*)arg;
    while(1)
    {
        printf("I'm create pthread,my arg is %d\n",*t);
        sleep(1);
    }

}

int main()
{
    pthread_t pt;
    int i = 4;
    int ret = pthread_create(&pt,NULL,pthreadEntry,(void*)&i);
    if(ret < 0)
    {
        perror("pthread_create");
        return 0;
    }
    //create success
    while(1)
    {
        puts("i am main pthread");
        sleep(1);
    }
    
    return 0;
}
