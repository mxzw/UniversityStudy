// 2019.3.29
// 利用类对象数组完成N个学生数据（学号是字符串类型、成绩是整型）的输入、输出。
#include<iostream>
#include<string>
using namespace std;
class Student{
public:
	Student(){
        // empty body
	}
	void setID( string x ){
		id = x;
	}
	void setScore( int y ){
		score = y;
	}
	void getData(){
		cout << id << " " << score << endl;
	} 

private:
    string id;
	int score; 
};
int main()
{
	int n;
    cin >> n;
    Student t[n];
	string x[n];
	int y[n];
	for( int i = 0; i < n; ++i ){
		cin >> x[i] >> y[i];
		t[i].setID(x[i]);
		t[i].setScore(y[i]);
	} 
	for( int j = 0; j < n; ++j ){
		t[j].getData();
	}
	return 0;
}
