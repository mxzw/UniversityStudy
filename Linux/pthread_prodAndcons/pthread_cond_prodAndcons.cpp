#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <queue>

using namespace std;

#define PTHREADNUM 4

//实现一个线程安全的队列
class SafeQueue
{
    public:
        //初始化队列
        SafeQueue() : que_(),capacity_(10)
        {
            pthread_mutex_init(&lock_,NULL);
            pthread_cond_init(&prod_,NULL);
            pthread_cond_init(&cons_,NULL);

        }
        //销毁队列
        ~SafeQueue()
        {
            pthread_mutex_destroy(&lock_);
            pthread_cond_destroy(&prod_);
            pthread_cond_destroy(&cons_);
        }

        //生产者入队操作
        void Push(int val)
        {
            /*
             * 1.首先要保证互斥，在往que_队列中插入的时候要加锁
             * 2.要对资源进行判断，当que_.size() == capacity_的时候，要进入生产者的PCB队列中进行等待
             * 3.最后，当插入完成之后，要唤醒处于消费者PCB等待队列的线程
             */ 
            pthread_mutex_lock(&lock_);
            //注意一定要是while循环判断，防止产生资源不合理的情况。
            while(que_.size() == capacity_)
            {
                pthread_cond_wait(&prod_,&lock_);
            }

            que_.push(val);
            printf("i am %p,i prod %d\n",pthread_self(),val);

            pthread_cond_signal(&cons_);
            pthread_mutex_unlock(&lock_);
        }
        void Pop(int* value)
        {
            /*
             * 1.为了保证互斥，要加锁
             * 2.要对资源进行判断，当que_.empty()为真的时候，要进入消费者的等待队列中进行阻塞
             * 3.当对资源操作完成之后，要唤醒生产者PCB等待队列中的值进行生产
             */ 
            pthread_mutex_lock(&lock_);
            
            while(que_.empty())
            {
                pthread_cond_wait(&cons_,&lock_);
            }

            *value = que_.front();
            que_.pop();
            printf("i am %p,i cons %d\n",pthread_self(),*value);
            
            pthread_cond_signal(&prod_);
            pthread_mutex_unlock(&lock_);

        }
    private:
        //使用 aaa_ 而不是 _aaa来命名成员变量，是为了与内核源码区分开来，这是谷歌的一种命名规范
        //在这个队列中实现对生产资源的操作
        queue<int> que_;
        //保证这个仓库的容量
        size_t capacity_;
        
        //保证互斥
        pthread_mutex_t lock_;
        //保证同步
        //1.生产者的条件变量
        pthread_cond_t prod_;
        //2.消费者的条件变量
        pthread_cond_t cons_;

};

//由于我们要对同一临界资源进行操作，因此，我们就需要对该临界资源加锁

int value = 0;
pthread_mutex_t g_lock;

//消费者线程---用来做消费
void* ConsumePthread(void* arg)
{
    SafeQueue* sq = (SafeQueue*) arg;
    while(1)
    {
        int data;
        sq->Pop(&data);
    }

    return NULL;
}

void* ProductPthread(void* arg)
{
    SafeQueue* sq = (SafeQueue*) arg;
    while(1)
    {
        pthread_mutex_lock(&g_lock);
        sq->Push(value);
        value++;
        pthread_mutex_unlock(&g_lock);
    }
    return NULL;

}

//在主线程中创建两个线程，一个为生产者线程，一个为消费者线程
int main()
{
    pthread_t tig_A[PTHREADNUM];
    pthread_t tig_B[PTHREADNUM];

    pthread_mutex_init(&g_lock,NULL);

    //由于两个线程要对同一个资源进行操作，因此需要传入同一个队列的地址
    //由于是多线程，因此我们需要在堆上开辟空间
    SafeQueue* sq = new SafeQueue();
    for(int i = 0; i < PTHREADNUM; ++i)
    {
        int ret = pthread_create(&tig_A[i],NULL,ConsumePthread,(void*)sq);
        if(ret < 0)
        {
            printf("ConsumePthread create failed\n");
            return 0;
        }
        ret = pthread_create(&tig_B[i],NULL,ProductPthread,(void*)sq);
        if(ret < 0)
        {
            printf("ProductPthread create failed\n");
            return 0;
        }
    }

    for(int i = 0; i < PTHREADNUM; ++i)
    {
        pthread_join(tig_A[i],NULL);
        pthread_join(tig_B[i],NULL);
    }

    pthread_mutex_destroy(&g_lock);

    return 0;
}
