#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

namespace myTest{
    //less<T> 是一个仿函数，表示当前比较的准则是小于，则建的堆就是大堆
    //greater<T> 也是仿函数，表示比较的准则是大于，则建的堆就是小堆
    template<typename T,class Cond = vector<T> , class Pred = less<T>>
        class priority_queue{
            public:
                explicit priority_queue() {}
                priority_queue(const T* first,const T* last)
                {
                    //1.首先建立一个数组
                    c_.insert(c_.begin(),first,last);
                    //2.其次再将建立的数组使用算法函数建成一个堆
                    make_heap(c_.begin(),c_.end(),pr_);
                }

                void push(const T x)
                {
                    //首先将数据插入到数组中
                    c_.push_back(x);
                    //调整数组，使其再次成为堆
                    push_heap(c_.begin(),c_.end(),pr_);
                }

                void pop()
                {
                    //首先需要将堆顶元素进行调整，在删除
                    pop_heap(c_.begin(),c_.end(),pr_);

                    c_.pop_back();
                }

                bool empty()const
                {
                    return c_.empty();
                }

                size_t size() const
                {
                    return c_.size();
                }
                T& top()const
                {
                    return c_.front();
                }
                //为了测试方便，我们编写一个打印函数
                void Print() const
                {
                    auto it = c_.begin();
                    while(it != c_.end())
                    {
                        cout << *it << " ";
                        it++;
                    }
                    cout << endl;

                }

            private:
                Cond c_;
                Pred pr_;//比较谓词
        };
}

void test()
{
    int iv[] = {1,7,9,0,3,5,2,4};
    int n = sizeof(iv) / sizeof(iv[0]);
    cout << "normal vector is ";
    for(int i = 0 ;i < n; ++i)
    {
        cout << iv[i] << " ";
    }
    cout << endl;
    myTest::priority_queue<int,vector<int>,greater<int>> pq(iv,iv+n);

    cout << "make_heap" << endl;
    pq.Print(); 
    cout << "push_heap(12)" << endl;
    pq.push(12);
    pq.Print();
    cout << "pop_heap" << endl;
    pq.pop();
    pq.Print();
}


int main()
{
    test();
    return 0;
}
