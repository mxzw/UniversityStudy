// 2019.3.29
//����-��������
#include <iostream>
using namespace std;
class A
{
public:
    A(int x){   //������ĳ�Ա��ʹ�ý�������ȷ
	num = x;
	cout << num << "--->���캯��" << endl;   
    }
    ~A(){
    cout << num << "--->��������" << endl;
	}
private:
	int num;
 
}; 
int main()
{
    A a(1),b(2);
cout<<"end of main"<<endl;
    return 0;
}
