//2019.3.4
//�����-��Ͷ���
#include<iostream> 
using namespace std;

class Max
{
private:
	int a,b,c;//���ݳ�Աa,b,c
public:
	void setMax(int q,int w,int e){  //���û��ȡa,b,cֵ�ĺ���
		a = q;
		b = w;
		c = e;
	}
	int getMax()const{    //��Ա����max(a,b,c) 
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
  Max max1;//��������
  int x,y,z,p;
  cin>>x>>y>>z;
  max1.setMax(x,y,z);
  p = max1.getMax();
  cout<<p<<endl;//�ö���ȥ���ó�Ա���� 
return 0;
} 
