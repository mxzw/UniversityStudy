// 2019.3.27
// ������A�����н��������캯��������������
//  ���ճ�������д����Ķ����������main�еĴ��롣 
#include<iostream>
using namespace std;
class Object{
public:
	Object( char b ){
		a = b;
		cout << "Constructing an object of " << a << endl;	
	}
	~Object(){
	cout << "Destructing an object of " << a << endl;
	}
private:
	char a;
}; 
int main()
{
	Object x('A');
	Object y('A');
	return 0;
}
