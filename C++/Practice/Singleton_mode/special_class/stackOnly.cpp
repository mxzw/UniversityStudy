#include <iostream>
class StackOnly1{
    public:
        StackOnly1()
        {}
    private:
        void* operator new(size_t size);
        void operator delete(void* p);
};

class StackOnly2{
    public:
        static StackOnly2 GetObject()
        {
            return StackOnly2();
        }
    private:
        StackOnly2()
        {}
};
