#include<iostream>
#include<iomanip>
#define pi 3.1415926
using namespace std;
int main(){
	float a,b;
	cin>>a>>b;
	cout.setf(ios::fixed);
	cout<<fixed<<setprecision(2)<<2*pi*a<<" ";
	cout<<fixed<<setprecision(2)<<pi*a*a<<" ";
	cout<<fixed<<setprecision(2)<<2*pi*b*a<<" ";
	cout<<fixed<<setprecision(2)<<pi*a*a*b<<endl;
	return 0; 
}
