//2019.3.29
//析构函数
#include <iostream>
using namespace std;
class A
{
public: 
A()
{
cout<<"构造函数"<<endl; 
}  
~A(){  //增加代码 
cout << "析构函数" << endl;
}       

}; 
int main()
{
    A a;
    A *p = new A();
    delete p; //添加一行代码 
cout<<"end of main"<<endl;
    return 0;
}


