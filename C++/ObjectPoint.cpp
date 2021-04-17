// 2019.3.29
/*建立对象数组，内放5个学生数据（学号是字符串类型、成绩是整型），
  设立max函数，用指向对象的指针作函数参数，
  在max函数中找出5个学生中成绩最高者，并输出其学号和成绩。 */
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
		cout << id << " " << score;
	} 
	int getScore(){
		return score;
	}
    	
private:
    string id;
	int score; 
};
void max( Student * );
int main()
{
	Student t[5];
	string x[5];
	int y[5];
	int l;
	for( int i = 0;i < 5;i++ ){
		cin >> x[i] >> y[i];
		t[i].setID(x[i]);
		t[i].setScore(y[i]);
	}
	max(t);
	return 0;
}
void max( Student *s ){
	int z[5],a;
	for( int i = 0; i < 5; ++i ){
	    
		z[i] = s->getScore();
		s++;
	}

	for( int i = 0; i < 5;++i ){
		for( int j = 0; j < 4;++j ){
			if( z[j] > z[j+1] ){
				a = z[j];
				z[j] = z[j+1];
				z[j+1] = a;
			}
		} 
	}

     s = s - 4;
	for( int i = 0;i < 5;i++ ){
		if( z[4] == s->getScore() ){
			s->getData();
			break;
		} 
		s++;
	}
	
}
