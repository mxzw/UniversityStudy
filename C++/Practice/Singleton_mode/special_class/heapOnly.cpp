#include <iostream>

using namespace std;

class heapOnly{
    public:
        static heapOnly* GetObject()
        {
            return new heapOnly;
        }
    private:
        heapOnly()
        {}
        //注意这里一定要用到delete方法来表示对该方法进行删除
        //这样做的目的是防止友元函数对该类拷贝构造的调用，从而导致在栈上开辟空间
        heapOnly(const heapOnly& h) = delete;

};
