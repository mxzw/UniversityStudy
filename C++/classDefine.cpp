//��Ķ���
// 2019.3.4 
#include <iostream>
using namespace std;
class Box{
public:
	void setLength(double a){
		Length = a;
	}
	void setBreadth(double b){
		Breadth = b;
	}
	void setHeight(double c){
		Height = c;
	}
	double getVolume()const{
		return Length*Breadth*Height;
	}
private:
	double Length,Breadth,Height;
};
int main( )
{
   Box Box1;                // ���� Box1������Ϊ Box
   Box Box2;                // ���� Box2������Ϊ Box
   double volume = 0.0;     // ���ڴ洢���
 
   // box 1 ����
   Box1.setLength(6.0); 
   Box1.setBreadth(7.0); 
   Box1.setHeight(5.0);
 
   // box 2 ����
   Box2.setLength(12.0); 
   Box2.setBreadth(13.0); 
   Box2.setHeight(10.0);
 
   // box 1 �����
   volume = Box1.getVolume();
   cout << "Box1 �������" << volume <<endl;
 
   // box 2 �����
   volume = Box2.getVolume();
   cout << "Box2 �������" << volume <<endl;
   return 0;
}

