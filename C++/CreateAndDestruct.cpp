// 2019.3.29
//构造-析构函数
#include <iostream>
using namespace std;
class A
{
public:
    A(int x){   //定义类的成员，使得结果输出正确
	num = x;
	cout << num << "--->构造函数" << endl;   
    }
    ~A(){
    cout << num << "--->析构函数" << endl;
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
