#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <queue>


using namespace std;

//我们将int作为要处理的数据类型
typedef int DataType;
//定义函数指针作为处理该数据的方法，返回值是void，参数是DataType
typedef void (*Handler)(DataType);

//首先我们需要定义一个队列的元素类型
class QueueType
{
    public:
        QueueType(DataType d,Handler h):data_(d),handler_(h)
    {}

        ~QueueType()
        {}

        //调用此接口，即可对数据进行处理，本质上就是调用函数指针处理该数据
        //当线程池中的线程从线程安全队列中拿到元素后，就调用该方法来处理数据
        void dealData()
        {
            handler_(data_);
        }

    private:
        DataType data_;
        Handler handler_;
};

//然后接下来我们就需要定义出线程池的类了
/*
 *首先，我们需要知道该类需要哪些成员变量
 * 1. 要有一个线程安全的队列，线程安全的实现采用互斥锁+条件变量
 * 2. 线程池的容量大小限制
 * 3. 由于线程池在启动线程的时候，可能会有一部分线程启动失败,因此我们需要一个变量来记录启动成功的线程数量
 * 4. 当线程池中的线程处理完自己所需要处理的函数的时候，就要进行线程退出，但是由于线程池中有众多的线程，每个线程之间是并行执行的，因此当我们整个线程池要退出的时候，就需要将某些还阻塞在PCB等待队列中的线程全部唤醒,因此就需要一个标志变量来标志，让当前还在运行的线程进行退出。
 */

/*
 * 其次，我们还要考虑当前这个线程池需要实现哪些功能
 * 1.构造函数：初始化成员变量
 * 2.析构函数：析构掉成员变量
 * 3.Push方法：将待要处理数据存入到线程安全队列中,相当于生产线程
 * 4.Pop方法：弹出当前队列的元素，注意它不是消费者，它只是单纯实现了元素的弹出而已
 * 5.线程创建函数：在线程池中创建线程
 * 6.线程池启动函数：启动线程池中的线程从队列中获取元素进行处理
 * 7.线程退出函数：当线程池要退出的时候，将所有处于PCB等待队列的线程唤醒，并使其退出。
 * */ 

#define PTHREADNUM 4
#define QueueSize 10

class MyPthreadPool
{
    public:
    MyPthreadPool()
    {
        capacity_ = QueueSize;
        pthread_mutex_init(&lock_,NULL);
        pthread_cond_init(&prod_,NULL);
        pthread_cond_init(&cons_,NULL);

        pthreadNum_ = PTHREADNUM;
        quitFlag_ = false;

    }
        ~MyPthreadPool()
        {
            pthread_mutex_destroy(&lock_);
            pthread_cond_destroy(&prod_);
            pthread_cond_destroy(&cons_);
        }

        //线程创建函数--传入需要创建的线程数，返回创建成功的线程数
        int threadCreate(int num = PTHREADNUM)
        {
            if(num != PTHREADNUM)
               pthreadNum_ = num;

            //记录创建失败的线程数量
            int failed = 0;
            for(int i = 0; i < pthreadNum_; ++i)
            {
                //我们在这里不需要线程的标识符，因此也就不需要对其进行保持
                pthread_t tid;
                /*
                 * 注意线程池中的线程都执行的是同样的入口函数。
                 * 并且我们要令线程池启动函数为静态成员函数
                 * 为什么呢？还记得线程入口函数的标准格式吗？
                 * 标准格式为：void* PthreadEntry(void* arg)
                 * 若是定义为普通的成员变量，那么他就是这样的：
                 * void* PthreadEntry(MyPthreadPool* const this,void* arg)
                 * 里面就会有一个隐藏的this指针，不符合格式，因此采用静态的成员函数
                 */
                int ret = pthread_create(&tid,NULL,PthreadPoolStart,this);
                if(ret < 0)
                {
                    ++failed;
                    printf("i create failed, i am %d\n",i);
                    //创建线程失败了，不能返回，要继续进行创建
                    continue;
                }
            }
            //printf("failed:%d\n",failed);

            pthreadNum_ -= failed;

            //若结果等于0，则说明创建失败
            if(pthreadNum_ == 0)
                return -1;

            return pthreadNum_;
        }
        //线程池启动函数,相当于是线程入口函数
        static void* PthreadPoolStart(void* arg)
        {
            //我们直接让线程分离掉，这样就不需要在外面进行线程等待了
            pthread_detach(pthread_self());
            MyPthreadPool* mtp = (MyPthreadPool*) arg;

            /*
             * 1. 在该函数中我们需要获取队列中的元素，并对其进行处理。
             * 2. 由于有多个线程，因此我们必须保证线程安全
             */ 
            while(1)
            {
                pthread_mutex_lock(&mtp->lock_);

                while(mtp->que_.empty())
                {

                    //注意这里一定要先判断是否该退出了
                    if(mtp->quitFlag_)
                    {
                        //走到这里说明已经拿到锁了，要对锁进行释放，要不然程序就可能卡死。
                        pthread_mutex_unlock(&mtp->lock_);
                        pthread_exit(NULL);
                    }
                    pthread_cond_wait(&mtp->cons_,&mtp->lock_);
                }

                QueueType* q;
                mtp->Pop(&q);

                pthread_mutex_unlock(&mtp->lock_);
                pthread_cond_signal(&mtp->prod_);

                //当我们已经拿到了队列的元素之后，我们就可以直接的释放锁和唤醒对应的线程了，不必等到处理完该元素后，再释放;那么由于线程之间是并行处理的，多个线程都在等着抢这一把锁，如果在处理完该元素再释放，那么程序的效率就会下降，得不偿失。

                q->dealData();


                //这里有一点很容易忽略，由于传入到队列中的元素都是在堆上动态开辟的空间，所以，我们处理完之后，一定要进行释放，否则就会造成内存泄漏。
                delete q;

            }
            return NULL;
        }

        //在这里面只是单纯的弹出元素
        //在这里不加锁的原因只是为了让所有线程退出的时候，都只能从线程入口函数进行退出
        void Pop(QueueType** q)
        {
            *q = que_.front();
            que_.pop();
        }

        int Push(QueueType* q)
        {
            /*
             * 1. 要往线程池中的队列插入元素，要实现线程安全，使用互斥锁+条件变量
             * 2. 当队列已经满了的时候，就进入生产者的PCB等待队列中等待被唤醒
             * 3. 这里需要注意的是，我们是调用一个线程往队列中不停的插入数据，所以当线程池退出的时候，不能在当前线程进行退出，否则就会造成程序卡死，因为没有线程进行对其进行等待，回收不到资源，若该线程为主线程，则会变为僵尸线程，其他工作线程将永远不会退出。
             */ 

            pthread_mutex_lock(&lock_);

            while(que_.size() >= capacity_)
            {
                if(quitFlag_)
                {
                    pthread_mutex_unlock(&lock_);
                    return -1;
                }
                pthread_cond_wait(&prod_,&lock_);
            } 

            //当我们调用线程池退出函数的时候，所有正在写的行为都要进行停止，所有读的行为也要停止，因此，我们还需在这里再进行一次判断。
            if(quitFlag_)
            {
                pthread_mutex_unlock(&lock_);
                return -1;
            }

            que_.push(q);

            pthread_mutex_unlock(&lock_);
            pthread_cond_signal(&cons_);
            return 0;
        }

        //线程池退出函数
        void ThreadPoolExit()
        {
            /*
             * 这里需要注意的是，我们要在这里改变quitFlag_的值，而这个变量，在其他的线程中也都正在被访问，因此，这里要对其进行加锁操作
             */ 
            pthread_mutex_lock(&lock_);

            if(quitFlag_ == false)
                quitFlag_ = true;

            pthread_mutex_unlock(&lock_);


            //这里我们需要使用broadcast来唤醒所有处于PCB等待队列中的线程，让他们在各自执行的语句中进行线程退出。
            pthread_cond_broadcast(&cons_);
            //这里需要明白的是，我们不需要唤醒生产者的PCB等待队列，因为自始至终往队列中插入元素的只有一个线程，本代码中是主线程

        }


    private:
            queue<QueueType*> que_;
            //线程池的容量
            size_t capacity_;

            pthread_mutex_t lock_;

            pthread_cond_t prod_;
            pthread_cond_t cons_;

            //线程池正常启动的线程数量
            int pthreadNum_;

            //线程池退出的标志位
            bool quitFlag_;
};

//定义处理数据的方法
void dealNum(DataType t)
{
    printf("i am deadlNum func ,i deal %d\n",t);
}

int main(int argc,char* argv[])
{
    /*
     * 1.首先我们需要在堆上开辟一个线程池的空间
     * 2.其次我们还需定义一个处理用户传入数据的函数
     * 3.我们需要在堆上开辟出空间，用来保持我们待向线程池插入的队列的元素类型
     * 4.我们可以利用命令行变量特性来确定每次线程池中线程的数量
     *
     */
    //用来获取命令行变量中用户输入的线程池的数量
    int thread_num = 0;
    for(int i = 0; i < argc;++i)
    {
        //printf("argv[%d] : %s\n",i,argv[i]);
        if(strcmp(argv[i],"-thread_num")== 0 && i + 1 < argc)
        {
            thread_num = atoi(argv[i+1]);
            //printf("thread_num is %d\n",thread_num);
        }
    }

    //定义线程池
    MyPthreadPool* mtp = new MyPthreadPool();
    if(mtp == NULL)
    {
        printf("create PthreadPool failed\n");
        return 0;
    }
    
    //初始化线程池
    int ret = mtp->threadCreate(thread_num);
    if(ret < 0)
    {
        printf("thread create failed\n");
        return 0;
    }

    printf("create success,thread_num is %d\n",ret);

    //向线程池的线程安全队列中插入数据
    for(int i = 0; i < 10000; ++i)
    {
        QueueType* q = new QueueType(i,dealNum);

        if(q==NULL)
            continue;

        //关于q的释放，会在线程池的线程处理完成之后，对对其进行释放，所以不用考虑内存泄漏的问题。
        mtp->Push(q);
    }
    //注意这里一定要sleep一下，由于线程是并行的，可能在主线程调用线程池退出函数的时候，线程池中的线程还没有来得及从线程安全队列中获取获取元素进行处理，就执行到了退出逻辑，就又可能造成程序的阻塞，比如最后几个数据处理不上的情况。
    //还有一种解决办法就是在退出的逻辑中，加上对对应条件变量的唤醒即可，也能解决这个问题
    sleep(2);

    //插入完之后，调用线程池退出函数
    mtp->ThreadPoolExit();


    delete mtp;

    while(1)
    {
        sleep(1);
    }
    return 0;
}
