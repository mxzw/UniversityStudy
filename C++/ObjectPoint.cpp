// 2019.3.29
/*�����������飬�ڷ�5��ѧ�����ݣ�ѧ�����ַ������͡��ɼ������ͣ���
  ����max��������ָ������ָ��������������
  ��max�������ҳ�5��ѧ���гɼ�����ߣ��������ѧ�źͳɼ��� */
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
