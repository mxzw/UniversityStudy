#include <iostream>
#include <deque>

namespace myTest{
    template<typename T, class Cond = deque<T>>
        class queue
        {
            public:
                queue(){}
                ~queue(){}

                void push(const T& x)
                {
                    c_.push_back(x);
                }
                void pop()
                {
                    c_.pop_front();
                }
                T& back()const
                {
                    return c_.back();
                }
                T& front()const
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
            private:
                Cond c_;
        };
}
