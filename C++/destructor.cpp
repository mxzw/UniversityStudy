//2019.3.29
//��������
#include <iostream>
using namespace std;
class A
{
public: 
A()
{
cout<<"���캯��"<<endl; 
}  
~A(){  //���Ӵ��� 
cout << "��������" << endl;
}       

}; 
int main()
{
    A a;
    A *p = new A();
    delete p; //���һ�д��� 
cout<<"end of main"<<endl;
    return 0;
}


