// 2019.3.29
//������������
#include <iostream>
using namespace std;
class A
{//���Ķ��������룬���ӹ��캯������������
//�����ȷ��� 
public: 
A(){
   cout << "���캯��" << endl; 
} 
~A(){
	cout << "��������" << endl;
}


}; 
int main()
{
    A a;
    return 0;
} 
