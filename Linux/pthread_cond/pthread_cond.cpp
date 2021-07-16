#include <stdio.h>
#include <unistd.h>
#include <pthread.h>



#define PTHREADNUM 2

int bowl = 1;

pthread_mutex_t g_lock;
pthread_cond_t g_condMake;
pthread_cond_t g_condEat;

//只负责吃的线程
void* MyPthreadEat(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&g_lock);
        //如果当碗中没饭的时候，则将该线程放入到PCB等待队列中，等待做饭的人做饭并将其唤醒
        while(bowl < 1)
        {
            pthread_cond_wait(&g_condEat,&g_lock);
        }
        //走到这说明碗中现在是有饭的
        --bowl;
        printf("i eat %d,i am %p\n",bowl,pthread_self());

        //在操作完之后，需要对负责做的PCB等待队列发出信号，唤醒正在等待通知的做的线程
        //pthread_cond_broadcast(&g_cond);
        pthread_cond_signal(&g_condMake);
        pthread_mutex_unlock(&g_lock);
    }
    return NULL;
}

//只负责做的线程
void* MyPthreadMake(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&g_lock);
        //如果当碗中有饭的时候，则将该线程放入到PCB等待队列中，等待吃饭的人吃饭并将其唤醒
        while(bowl >= 1)
        {
            pthread_cond_wait(&g_condMake,&g_lock);
        }
        //走到这说明碗中现在是没饭的
        ++bowl;
        printf("i make %d,i am %p\n",bowl,pthread_self());

        //在操作完之后，需要对负责吃的PCB等待队列发出信号，唤醒正在等待通知的吃的线程
        //pthread_cond_broadcast(&g_cond);
        pthread_cond_signal(&g_condEat);
        pthread_mutex_unlock(&g_lock);
    }
    
    return NULL;
}

int main()
{
    pthread_mutex_init(&g_lock,NULL);
    pthread_cond_init(&g_condEat,NULL);
    pthread_cond_init(&g_condMake,NULL);

    pthread_t tid_A[PTHREADNUM] , tid_B[PTHREADNUM];

    for(int i = 0;i < PTHREADNUM; ++i)
    {
        int ret = pthread_create(&tid_A[i],NULL,MyPthreadEat,NULL);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
        ret = pthread_create(&tid_B[i],NULL,MyPthreadMake,NULL);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }    
    }

    for(int i = 0; i < PTHREADNUM; ++i)
    {
        pthread_join(tid_A[i],NULL);
        pthread_join(tid_B[i],NULL);
    }
    pthread_mutex_destroy(&g_lock);
    pthread_cond_destroy(&g_condEat);
    pthread_cond_destroy(&g_condMake);
    return 0;
}
