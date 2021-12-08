#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

namespace mytest{
    class string;
    class stringRefC
    {
        friend ostream& operator<<(ostream& out,const stringRefC& s);
        friend class string;
        private:
        int ref_count;
        char* _arr;
        public:
        stringRefC(const char* s = "") : ref_count(0)
        {
            _arr = new char[strlen(s)+1];
            strcpy(_arr,s);
        }
        stringRefC(const stringRefC& s);


        void increaseCount()
        {
            ++ref_count;
        }

        void decraseCount()
        {
            if(--ref_count == 0)
            {
                //如果当计数器为0的时候，就调用自己的析构函数
                delete this;
            }
        }
        
        int use_count()const
        {
            return ref_count;
        }

        ~stringRefC()
        {
            if(ref_count == 0)
            {
                delete []_arr;
                _arr = nullptr;
            }
        }


    };
    class string{
        friend class stringRefC;
        friend ostream& operator<<(ostream& out,const string& s);
        private:
        stringRefC* _ref; 
        public:
        explicit string(): _ref(nullptr)
        {}
        string(const char* s= ""):_ref(new stringRefC(s))
        {
            _ref->increaseCount();
        }
        string(const string& s) : _ref(s._ref)
        {
            _ref->increaseCount();
        }
        string& operator=(const string& s)
        {
            if(this != &s)
            {
                _ref->decraseCount();
                _ref = s._ref;
                _ref->increaseCount();
            }
            return *this;
        }

        ~string()
        {
            _ref->decraseCount();
        }
    };
    
     ostream& operator<<(ostream& out,const string& s)
       {
           out << s._ref << ",ref_count = " << s._ref->use_count();
           return out;
       }
};

void test()
{
    mytest::string s("abc");
    cout << "s:" << s << endl;
    mytest::string r("def");
    cout << "r:" << r << endl;

    cout << "copyonwrite:r = s" << endl;
    r = s;
    cout << "r:" << r << endl;

    cout << "copyonwrite: string k(r)" << endl;
    mytest::string k(r);
    cout << "k:" << k << endl;


}

int main()
{
    test();
    return 0;
}
