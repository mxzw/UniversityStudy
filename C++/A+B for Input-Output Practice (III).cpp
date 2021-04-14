#include<iostream>
using namespace std;
int main()
{
	int a,b,c[1000],j=0;
	while(cin>>a>>b){
		if(a==0&&b==0){
			break;
		}
		c[j]=a+b;
		j++;
	}
	for(int i = 0;i<=j-1;i++){
		cout<<c[i]<<endl;
	}
	return 0;
}
