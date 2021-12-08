#include <iostream>
using namespace std;

class Test
{
    public:
        //构造函数
        Test()
        {
            cout << "Test to create class" << endl;
        }
        Test(int data)
        {
            this->_data = data;
        }
        //带默认参数的构造函数,只能和Test()互存一个
        /* Test(int data = 0)
           {
           this->_data = data;
           }*/
        //拷贝构造函数
        Test(const Test &t)
        {
            cout << "This is copy create func" << endl;
            this->_data = t._data;
        }

        //赋值运算符重载
        Test& operator=(const Test &t)
        {
            cout<<"Assgin."<<this<<" : "<<&t<<endl;
            if(this != &t)
            {
                this->_data = t._data;

            }
            return *this;
        }

        void GetData()
        {
            cout << "Test no const!" << endl;
        }

        void GetData() const
        {
            cout << "Test const!" << endl;
        }

        //析构函数
        ~Test()
        {
            cout << "free to this class" << endl;
        }

    private:
        int _data;
};

int main()
{
    const Test t;
    t.GetData();
    return 0;
}
