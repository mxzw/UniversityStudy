// 2019.3.27
// 创建类A；类中仅包含构造函数和析构函数，
//  按照程序的输出写出类的定义和主函数main中的代码。 
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
