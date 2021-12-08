#include <iostream>
#include <cstring>

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

            string(const string& s)
            {
                _arr = new char[strlen(s._arr)+1];
                strcpy(_arr,s._arr);
            }

            string& operator=(const string& s)
            {
                if(this != &s)
                {
                    //存在异常不安全的问题，若是_arr申请空间失败，那么我又已经把原来的空间释放掉了，这就造成了异常不安全的情况。
                    //所谓异常不安全就是在程序发生异常的时候，原来的指针、空间、内存等状态安不安全，或者是说被修改了。
                    //异常安全也可以说是即使在抛出异常的时候（如果有异常的话），程序回退的过程是干净的
                    delete []_arr;
                    _arr = new char[strlen(s._arr)+1];
                    strcpy(_arr,s._arr);
                }
                return *this;
            }

            ~string()
            {
                delete[] _arr;
                _arr = nullptr;
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
