#include <iostream>
#include <vector>
#include <functional>

using namespace std;

namespace myTest{
    template<typename T,class Cond = vector<T>,class Pred = less<T>>
        class priority_queue{
            public:
                explicit priority_queue() 
                {}
                priority_queue(const T* first,const T* last)
                {
                    c_.insert(c_.begin(),first,last);

                    //建堆----使用向下调整算法
                    //从最后一个非叶子节点开始调
                    for(int i = ((c_.size()-1)-1) >> 1;i >= 0; --i)
                    {
                        AdjustDown(i);
                    }

                }

                void push(const T x)
                {
                    c_.push_back(x);

                    //插入到数组的末尾，使用向上调整算法进行调堆
                    AdjustUp(c_.size()-1);

                }


                void pop()
                {
                    //首先交换堆顶元素和堆尾元素，然后再进行调堆
                    std::swap(c_.front(),c_.back());
                    
                    c_.pop_back();

                    AdjustDown(0);

                }

                T& top()const
                {
                    return c_.front();
                }

                size_t size() const
                {
                    return c_.size();
                }

                bool empty()const
                {
                    return c_.empty();
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

            protected:
                void AdjustDown(int parent)
                {
                    int child = parent * 2 + 1;
                    while(child < c_.size())
                    {
                        if(child + 1 < c_.size() && pr_(c_[child],c_[child + 1]))
                            ++child;
                        if(pr_(c_[parent],c_[child]))
                        {
                            std::swap(c_[child],c_[parent]);
                            parent = child;
                            child = parent * 2 + 1;
                        }
                        else
                            break;
                    }
                }
                void AdjustUp(int child)
                {
                    int parent = (child-1) >> 1;
                    while(parent > 0)
                    {
                        if(pr_(c_[parent],c_[child]))
                        {
                            std::swap(c_[child],c_[parent]);
                            child = parent;
                            parent = (child-1) >> 1;
                        }
                        else
                            break;
                    }
                }

            private:
                Cond c_;
                Pred pr_;

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

    cout << "create heap" << endl;
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
