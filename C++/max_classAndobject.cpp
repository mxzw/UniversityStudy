//2019.3.4
//求最大-类和对象
#include<iostream> 
using namespace std;

class Max
{
private:
	int a,b,c;//数据成员a,b,c
public:
	void setMax(int q,int w,int e){  //设置或读取a,b,c值的函数
		a = q;
		b = w;
		c = e;
	}
	int getMax()const{    //成员函数max(a,b,c) 
	if(a>=b&&a>=c){
		return a;
	}
	if(b>=a&&b>=c){
		return b;
	}
	if(c>=a&&c>=b){
		return c;
	}	
	}                                    
};

int main()
{
  Max max1;//创建对象
  int x,y,z,p;
  cin>>x>>y>>z;
  max1.setMax(x,y,z);
  p = max1.getMax();
  cout<<p<<endl;//用对象去调用成员函数 
return 0;
} 
