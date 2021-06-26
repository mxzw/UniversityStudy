#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

typedef struct mytest{
    int i;
}mytest;

void* pthreadEntry(void* arg)
{
    mytest* t = (mytest*) arg;
    while(1)
    {
        printf("I'm create pthread,my arg is %d\n",t->i);
        sleep(1);
    }
    delete t;

}

int main()
{
    pthread_t pt;
    for(int i = 0; i < 4; ++i)
    {
        mytest* t = (mytest*)malloc(sizeof(mytest));
        t->i = i;
        int ret = pthread_create(&pt,NULL,pthreadEntry,(void*)t);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }

    }

    //create success
    while(1)
    {
        puts("i am main pthread");
        sleep(1);
    }

    return 0;
}
