#include <iostream>
#include <time.h>
using namespace std;

struct A{ int a[10000];  };

void swap(int& a,int& b)    
{    
    int tmp = a;    
    a = b;    
    b = tmp;    
}  

void TestFunc1(A a){}

void TestFunc2(A& a){}

void TestRefAndValue()
{
    A a;
    // 以值作为函数参数
    size_t begin1 = clock();
    for (size_t i = 0; i < 10000; ++i)
        TestFunc1(a);
    size_t end1 = clock();
    // 以引用作为函数参数
    size_t begin2 = clock();
    for (size_t i = 0; i < 10000; ++i)
        TestFunc2(a);
    size_t end2 = clock();
    // 分别计算两个函数运行结束后的时间
    cout << "TestFunc1(A)-time:" << end1 - begin1 << endl;
    cout << "TestFunc2(A&)-time:" << end2 - begin2 << endl;

}

int main()
{
    //TestRefAndValue();
    int a = 1, b = 2; 
    cout << "swap之前：a的值为：" << a << "，b的值为：" << b << endl;
    swap(a,b);
    cout << "swap之后：a的值为：" << a << "，b的值为：" << b << endl;
    return 0;
}
