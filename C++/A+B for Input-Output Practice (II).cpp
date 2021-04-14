#include<iostream>
using namespace std;
int main()
{
	int i,j=0;
	int a,b,c[1000];
	cin>>i;
	while(j<i){
		cin>>a>>b;
		c[j]=a+b;
		j++;
	}
	for(int x=0;x<=j-1;x++){
		cout<<c[x]<<endl;
	}
	return 0;
}
