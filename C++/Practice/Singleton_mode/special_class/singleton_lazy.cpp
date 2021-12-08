#include <iostream>
#include <mutex>
#include <thread>
using namespace std;


class singleton{
    public:
        static singleton* GetObject()
        {
            if(psg == nullptr)
            {
                mt.lock();
                if(psg == nullptr)
                {
                    psg = new singleton;
                }
                mt.unlock();
            }
            return psg;
        }

        //我们在这里定义一个回收类，专门用来回收我们在堆上申请的空间
        class Recycle{
            public:
                ~Recycle()
                {
                    if(psg)
                        delete singleton::psg;
                }
        };

        //由于懒汉模式下只会产生一个对象，因此当程序结束时，
        //rc再调用析构函数的时候就会对我们动态申请的psg空间进行释放。
        static Recycle rc;

    private:
        singleton()
        {}

        singleton(const singleton& sg) = delete;
        singleton& operator=(const singleton& sg) = delete;

        //这样这里不能用该静态的对象，因为这是懒汉模式，
        //只有在需要用到它的时候才会创建对象
        static singleton* psg;
        //加上锁变量是为了保证线程安全
        static mutex mt;
};

singleton* singleton::psg = nullptr;
mutex singleton::mt;
singleton::Recycle rc;

