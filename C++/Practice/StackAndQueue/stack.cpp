#include <iostream>
#include <deque>

using namespace std;

namespace myTest{
    template<typename T,class Cond = deque<T>>
        class stack{
            public:
                stack(){}
                ~stack(){}
                void push(T& x)
                {
                    c_.push_back(x);
                }
                void pop()
                {
                    c_.pop_back();
                }
                T& top() const
                {
                    return c_.back();
                }
                size_t size()const 
                {
                    return c_.size();
                }
                bool empty()const
                {
                    return c_.empty();
                }

            private:
                Cond c_;
        };
}
