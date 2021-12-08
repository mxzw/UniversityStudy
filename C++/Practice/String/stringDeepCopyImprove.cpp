#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

namespace mytest{
    class string{
        friend ostream& operator<<(ostream& out,const string& s);
        private:
            char* _arr;
        public:
            explicit string(): _arr(nullptr)
            {}
            string(const char* s = "")
            {
                _arr = new char[strlen(s)+1];
                strcpy(_arr,s);
            }

            //程序是异常安全的，因为如果空间不足，程序就会抛出异常，并且回退的过程中都是干净的
            string(const string& s):_arr(nullptr)
            {
                //注意这里一定要用一个string来接收
                //若为char* tmp = s._arr 来写的话会造成Double Free问题
                //因为tmp指向的是s._arr的那个空间，当s释放之后，当前对象再次进行释放的时候就会对_arr那个空间进行重复的释放。
                string tmp(s._arr);
                std::swap(_arr,tmp._arr);
            }

            string& operator=(const string& s)
            {
                if(this != &s)
                {
                    //用一个临时变量来进行接收有两大好处
                    //1.tmp是调用了拷贝构造函数进行初始化的，该过程是异常安全的
                    //2.因为tmp是临时变量，因此在赋值重载完了后，就会自动的调用析构函数进行析构，我们不必自己单独的将原来的_arr空间释放掉，然后在交换了，这样做的简直就是一举三得。
                    string tmp(s);
                    std::swap(_arr,tmp._arr);
                }
                return *this;
            }

            ~string()
            {
                if(_arr)
                {
                    delete[] _arr;
                    _arr = nullptr;
                }
            }


    };

     ostream& operator<<(ostream& out,const string& s)
     {
         out << s._arr;
         return out;
     }
}

void test()
{
    mytest::string s("dsa");
    cout << s << endl;

    mytest::string r(s);
    cout << r << endl;

    mytest::string rt("xyz");
    cout << rt << endl;

    rt = r;
    cout << rt << endl;

}

int main()
{
    test();
    return 0;
}
