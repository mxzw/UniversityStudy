#include<iostream>
#include<iomanip> 
using namespace std;
int main(){
	int a,b,c;
	cin>>a>>b>>c;
	cout.setf(ios::fixed);
	cout<<a+b+c<<" "<<a*b*c<<" "<<fixed<<setprecision(2)<<(a+b+c)/3.0<<endl;
	return 0;
}//cout.setf(ios::fixed)  setprecision
