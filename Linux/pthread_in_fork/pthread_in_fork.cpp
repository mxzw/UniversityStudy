#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <iostream>
using namespace std;


pthread_mutex_t mt;

void* pthreadFork(void * arg)
{
    pthread_detach(pthread_self());

    sleep(2);
    int ret = fork();
    if(ret < 0)
    {
        cout << "fork failed" << endl;
        return 0;
    }
    else if(ret == 0)
    {
        //child
        cout << "It's Child !" << endl;
        while(1)
        {
            pthread_mutex_lock(&mt);
            cout << "It's test pthreadFork_Child " << endl;
            pthread_mutex_unlock(&mt);
        }
    }
    else
    {
        //father
        cout << "It's father!" << endl;
        wait(NULL);
    }

    return NULL;
}

void* pthreadLock(void * arg)
{
    pthread_detach(pthread_self());
    while(1)
    {
        pthread_mutex_lock(&mt);
        cout << "It's pthreadLock" << endl;
        sleep(3);
        pthread_mutex_unlock(&mt);
    }
    return NULL;
}

int main()
{
    pthread_t pid;

    pthread_mutex_init(&mt,NULL);
    int ret = pthread_create(&pid,NULL,pthreadFork,NULL);
    if(ret < 0)
    {
        cout << "pthread failed" << endl;
        return 0;
    }

    ret = pthread_create(&pid,NULL,pthreadLock,NULL);
    if(ret < 0)
    {
        cout << "pthread failed" << endl;
        return 0;
    }

    while(1)
    {
        sleep(1);
    }

    pthread_mutex_destroy(&mt);
    return 0;
}
