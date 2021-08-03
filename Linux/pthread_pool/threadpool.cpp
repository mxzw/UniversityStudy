#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <queue>

using namespace std;
#define QUEUE_SIZE 1
#define THREAD_NUM 1

//设计线程安全队列的类型

typedef void (*Handler)(int);

class QueueType
{
    public:
        QueueType(int data, Handler handler)
        {
            data_ = data;
            handler_ = handler;
        }

        ~QueueType()
        {

        }

        /*
         * 线程从线程池当中线程安全队列获取一个元素之后
         * 拿到该类型， 通过该类型当中“deal”方法处理数据
         * */
        void Deal()
        {
            handler_(data_);
        }
    private:
        //待要处理的数据
        int data_;
        //处理数据的方法
        Handler handler_;
};


class MyThreadPool
{
    public:
        MyThreadPool()
        {
            capacity_ = QUEUE_SIZE;
            pthread_mutex_init(&lock_, NULL); 

            pthread_cond_init(&cons_cond_, NULL);
            pthread_cond_init(&prod_cond_, NULL);
            thread_count_ = THREAD_NUM;

            is_quit_ = false;
        }

        ~MyThreadPool()
        {
            pthread_mutex_destroy(&lock_);
            pthread_cond_destroy(&cons_cond_);
            pthread_cond_destroy(&prod_cond_);
        }

        int InitAndStart(int thread_num = THREAD_NUM)
        {
            if(thread_num != THREAD_NUM)
            {
                thread_count_ = thread_num;
            }

            int fail_count = 0;
            for(int i = 0; i < thread_count_; i++)
            {
                pthread_t tid;
                int ret = pthread_create(&tid, NULL, ThreadPoolStart, this);
                if(ret < 0)
                {
                    fail_count++;
                    printf("create thread failed, %d\n", i);
                    continue;
                }
            }

            thread_count_ -= fail_count;

            if(thread_count_ == 0)
            {
                return -1;
            }
            return thread_count_;
        }

        static void* ThreadPoolStart(void* arg)
        {
            pthread_detach(pthread_self());
            MyThreadPool* mtp = (MyThreadPool*)arg;
            while(1)
            {
                pthread_mutex_lock(&mtp->lock_);
                //1.从队列当中获取
                while(mtp->que_.empty())
                {
                    if(mtp->is_quit_)
                    {
                        pthread_mutex_unlock(&mtp->lock_);
                        pthread_exit(NULL);
                    }
                    pthread_cond_wait(&mtp->cons_cond_, &mtp->lock_);
                }
                QueueType* q;
                mtp->Pop(&q);

                pthread_mutex_unlock(&mtp->lock_);
                pthread_cond_signal(&mtp->prod_cond_);
                //2.处理数据
                q->Deal();

                /*QueueType* qt = new QueueType(i, DealNum);
                 * delete q：释放的是上面的动态开辟的内存
                 */
                delete q;
            }
            return NULL;
        }

        int Push(QueueType* q)
        {
            pthread_mutex_lock(&lock_);
            while(que_.size() >= capacity_)
            {
                if(is_quit_)
                {
                    pthread_mutex_unlock(&lock_);
                    
                    return -1;
                }
                pthread_cond_wait(&prod_cond_, &lock_);
            }

            if(is_quit_)
            {
                pthread_mutex_unlock(&lock_);
                return -1;
            }
            que_.push(q);
            pthread_mutex_unlock(&lock_);
            pthread_cond_signal(&cons_cond_);
            return 0;
        }

        void Pop(QueueType** q)
        {
            *q = que_.front();
            que_.pop();
        }

        void ThreadExit()
        {
            //1.change flag
            pthread_mutex_lock(&lock_);
            if(is_quit_ == false)
            {
                is_quit_ = true;
            }
            pthread_mutex_unlock(&lock_);

            //broadcast
            pthread_cond_broadcast(&cons_cond_);
        }

    private:
        queue<QueueType*> que_;
        size_t capacity_;

        pthread_mutex_t lock_;
        pthread_cond_t cons_cond_;
        pthread_cond_t prod_cond_;

        int thread_count_;

        bool is_quit_;
};

void DealNum(int data)
{
    printf("i am DealNum func, i deal %d\n", data);
}

int main(int argc, char* argv[])
{
    int thread_num = 0;
    for(int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "-thread_num") == 0 && i + 1 < argc)
        {
            thread_num = atoi(argv[i + 1]);
        }
    }

    MyThreadPool* mtp = new MyThreadPool();
    if(mtp == NULL)
    {
        printf("create threadpool failed\n");
        return 0;
    }

    int ret = mtp->InitAndStart(thread_num);
    if(ret < 0)
    {
        printf("thread all create failed\n");
        return 0;
    }

    printf("creaete success, thread_count: %d\n", ret);

    for(int i = 0; i < 2; i++)
    {
        //向线程池当中的线程安全队列当中放数据
        QueueType* qt = new QueueType(i, DealNum);
        if(qt == NULL)
        {
            continue;
        }
        mtp->Push(qt);
    }

    mtp->ThreadExit();

    delete mtp;

    while(1)
    {
        sleep(1);
    }
    return 0;
}
