#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <iostream>
#include <queue>

using namespace std;

#define CAPACITY 10
#define PTHREADNUM 2

class SafeQueue
{
    public:
        SafeQueue() : iv_(CAPACITY),capacity_(CAPACITY)
        {
            //用于线程间并要实现互斥，就要将其初始化为1
            sem_init(&lock_,0,1);
            
            //读线程的刚开始时数组中没有数，因此初始化为0
            sem_init(&read_,0,0);

            //由于刚开始时所要写的数组中没有数，因此信号量的值为capacity_
            sem_init(&write_,0,capacity_);

            //读和写的位置刚开始均为0
            pos_read = 0;
            pos_write = 0;
        }

        ~SafeQueue()
        {
            sem_destroy(&lock_);
            sem_destroy(&read_);
            sem_destroy(&write_);
        }

        void Push(int val)
        {
            /*
             * 1.这里一定要注意，不能先加锁，若是先加锁，那么当拿到这把锁之后，如果此时写的资源数已经没有了，那么就会进入PCB等待队列进行等待，并且这把锁还没有释放，造成程序的卡死，也可以称为死锁。因此，一定不要先加锁。
             * 2.在pos_write位置进行写入数据,并且要更新pos的位置
             * 3.最后再对信号量进行唤醒，保证正常的运行
             */
            sem_wait(&write_);

            sem_wait(&lock_);
            //在此处对数组进行写
            iv_[pos_write] = val;
            pos_write = (pos_write + 1) % capacity_;

            printf("i write %d,i am %p\n",val,pthread_self());
            sem_post(&lock_);

            sem_post(&read_);
        }

        void Pop(int* val)
        {
            //操作和Push方法一模一样，这里就不再做过多解释
            sem_wait(&read_);
            
            sem_wait(&lock_);
            *val = iv_[pos_read];

            pos_read = (pos_read + 1) % capacity_;

            printf("i read %d,i am %p\n",*val,pthread_self());
            sem_post(&lock_);

            sem_post(&write_);
            
        }
    private:
        vector<int> iv_;
        size_t capacity_;

        //保证互斥，初始为1
        sem_t lock_;
        //保证同步
        //1.写线程的信号量
        sem_t write_;
        //2.读线程的信号量
        sem_t read_;

        //同时需要再定义两个变量，标识当前读的位置和写的位置
        int pos_read;
        int pos_write;
};

int g_val = 0;
sem_t g_lock;

void* ReadPthread(void* arg)
{
    SafeQueue* sq = (SafeQueue*) arg;

    while(1)
    {
        int data;
        sq->Pop(&data);
    }
    
    return NULL;
}

void* WritePthread(void* arg)
{
    SafeQueue* sq = (SafeQueue*) arg;

    while(1)
    {
        sem_wait(&g_lock);

        sq->Push(g_val);
        g_val++;

        sem_post(&g_lock);
    }
    return NULL;
}

int main()
{
    pthread_t tid_A[PTHREADNUM];
    pthread_t tid_B[PTHREADNUM];

    sem_init(&g_lock,0,1);

    SafeQueue* sq = new SafeQueue();

    for(int i = 0; i < PTHREADNUM;++i)
    {
        int ret = pthread_create(&tid_A[i],NULL,ReadPthread,(void*)sq);
        if(ret < 0)
        {
            printf("pthread_create failed\n");
            return 0;
        }
        ret = pthread_create(&tid_B[i],NULL,WritePthread,(void*)sq);
        if(ret < 0)
        {
            printf("pthread_create failed\n");
            return 0;
        }
    }

    for(int i = 0; i < PTHREADNUM; ++i)
    {
        pthread_join(tid_A[i],NULL);
        pthread_join(tid_B[i],NULL);
    }
    
    sem_destroy(&g_lock);
    return 0;
}
