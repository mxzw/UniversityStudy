// 2019.3.29
//析构函数定义
#include <iostream>
using namespace std;
class A
{//不改动其它代码，增加构造函数和析构函数
//输出正确结果 
public: 
A(){
   cout << "构造函数" << endl; 
} 
~A(){
	cout << "析构函数" << endl;
}


}; 
int main()
{
    A a;
    return 0;
} 
