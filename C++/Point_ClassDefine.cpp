// 2019.3.4
// Point��Ķ���
/*���һ������Point��������˽�����ݳ�Աx(������)��y(������)��
���г�Ա������SetPoint(int,int)�������õ�����ֵ��ShowPoint()���������������Ϣ.
���������е��ó�Ա����SetPoint(int,int)Ϊ���������ֵ��
�����ó�Ա����ShowPoint()��������Ϣ��*/
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

