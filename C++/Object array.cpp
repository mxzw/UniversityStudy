// 2019.3.29
// ����������������N��ѧ�����ݣ�ѧ�����ַ������͡��ɼ������ͣ������롢�����
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
