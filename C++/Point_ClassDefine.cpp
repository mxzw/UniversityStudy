// 2019.3.4
// Point类的定义
/*设计一个点类Point，它具有私有数据成员x(横坐标)、y(纵坐标)；
公有成员函数：SetPoint(int,int)用于设置点对象的值，ShowPoint()用于输出点对象的信息.
在主函数中调用成员函数SetPoint(int,int)为点对象设置值，
并调用成员函数ShowPoint()输出点的信息。*/
#include<iostream>
#include<string>
using namespace std;
class Point{
private:
	int x,y;
public:
	void SetPoint(int a,int b){
		x = a;
		y = b;
	}
	void ShowPoint()const{
		cout<<"("<<x<<","<<y<<")"<<endl;
	}
};
int main()
{
	Point myPoint;
	myPoint.SetPoint(10,11);
	myPoint.ShowPoint();
	return 0;
}

