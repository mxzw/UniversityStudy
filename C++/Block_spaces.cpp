#include<iostream>
using namespace std;
int main(){
int sum=0;
int c;
while(cin>>c){
sum+=c;
while(cin.peek()==' '){ //фа╠н©у╦Я
cin.get();
}
if(cin.peek()=='\n'){
break;
}
}
cout<<sum<<endl;
return 0;
}

