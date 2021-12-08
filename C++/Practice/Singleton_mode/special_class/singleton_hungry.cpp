#include <iostream>
using namespace std;

class singleton
{
    public:
        static singleton* GetObject()
        {
            //注意我们要返回该静态对象的指针，不能返回它的对象
            //因为该类的拷贝构造和赋值重载均被定义为私有的，并进行了删除声明
            return &sg;
        }
    private:
        singleton()
        {}

        singleton(const singleton &e) = delete;
        singleton operator=(const singleton &e) = delete;

        static singleton sg;
};

//在程序入口之前就完成该对象的初始化
singleton singleton::sg;

