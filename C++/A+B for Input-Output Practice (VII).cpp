#include<iostream>
using namespace std;
int main()
{
	int j=1;
	int a,b,c=0,d;
	while(cin>>a>>b){
		c=a+b;
		if(j==1){
			d=c;
		}
		if(j==2){
			break;
		}
		++j;
	}
	cout<<d<<endl<<"\n"<<c<<endl;
	return 0;
}
