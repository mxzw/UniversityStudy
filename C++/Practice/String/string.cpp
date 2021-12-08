#include <iostream>
#include <assert.h>
#include <cstring>
#include <algorithm>

using namespace std;


namespace mytest{
    class string
    {
        friend ostream& operator<<(ostream& out,const string& s);
        public:
        explicit string() : _arr(nullptr),_size(0),_capacity(0)
        {}
        string(const char* s) : _arr(nullptr),_size(0),_capacity(0)
        {
            _size = strlen(s);
            _capacity = _size;
            _arr = new char[_size];
            strcpy(_arr,s);
        }
        string(const string& s):_arr(nullptr),_size(0),_capacity(0)
        {
            string tmp(s._arr);
            swap(tmp);
        }
        string& operator=(const string& s)
        {
            if(this != &s)
            {
                string tmp(s._arr);
                swap(tmp);
            }
            return *this;
        }
        ~string()
        {
            if(_arr)
            {
                delete []_arr;
                _arr = nullptr;
            }
        }
        public:
        typedef char* iterator;
        //iterator
        iterator begin() const
        {
            return _arr;
        }
        iterator end() const
        {
            return _arr+_size;
        }

        iterator insert(iterator pos,char c)
        {
            if(_size == _capacity)
            {
                size_t oldpos = pos - begin();
                size_t newcapacity = _capacity == 0? 1 : 2*_capacity;
                //先扩容
                resever(newcapacity);

                pos = begin() + oldpos;
            }
            iterator it = end();
            while(it > pos)
            {
                *it = *(it-1);
                --it;
            }
            *pos = c;
            _size++;
            _arr[_size] = '\0';
            return pos;
        }
        string& insert(size_t pos,char c)
        {
            if(_size == _capacity)
            {
                //扩容
                size_t newcapacity = _capacity == 0 ? 1 :  2*_capacity;
                resever(newcapacity);
            }
            size_t sz = size();
            while(sz > pos)
            {
                _arr[sz] = _arr[sz-1];
                --sz;
            }
            _arr[pos] = c;
            ++_size;
            _arr[_size] = '\0';
            return *this;
        }

        string& insert(size_t pos, const char* str)
        {
            size_t len = strlen(str);
            if(_size == _capacity)
            {
                size_t newcapacity = _capacity + len;
                resever(newcapacity);
            }

            size_t sz = _size - 1;
            while(sz >= pos)
            {
                _arr[sz+len-1] = _arr[sz];
                --sz;
            }

            for(size_t i = 0; i < len && pos <= sz;++i)
            {
                _arr[pos++] = str[i];
            }
            _size = _size + len;
            _arr[_size] = '\0';
            return *this;
        }

        static const size_t npos = -1;
        string& erase(size_t pos=0 ,size_t len=npos)
        {
            size_t end = pos + len;
            if(len == npos)
                end = size();
            while(end < size())
            {
                _arr[pos++] = _arr[end++];
            }
            if(len== npos)
                _size = pos;
            else 
                _size = _size - len;
            _arr[_size] = '\0';
            return *this; 
        }

        //capacity
        size_t size() const
        {
            return _size;
        }
        size_t capacity() const
        {
            return _capacity;
        }
        size_t length()const
        {
            return _size;
        }
        void resever(size_t newcapacity)
        {
            if(_capacity < newcapacity)
            {
                //扩容
                char* tmp = new char[newcapacity];
                strcpy(tmp,_arr);
                std::swap(tmp,_arr);
                _capacity = newcapacity;
                delete []tmp;
            }
        }

        void resize(size_t newsize,char t = ' ')
        {
            if(newsize > _capacity)
            {
                //扩容
                resever(newsize);
                memset(_arr+_size,t,newsize - _size);
            }

            _arr[newsize] = '\0';
            _size = newsize;
        }


        public:
        //modify
        void clear()
        {
            erase();
        }
        void push_back(char c)
        {
            insert(end(),c);
        }

        string& operator+=(char c)
        {
            push_back(c);
            return *this;
        }
        void swap(string& s)
        {
            std::swap(_arr,s._arr);
            std::swap(_size,s._size);
            std::swap(_capacity,s._capacity);
        }
        void append(const char* str)
        {
            size_t len = strlen(str);

            if(_size + len > _capacity)
            {
                size_t newcapacity = _size + len;
                resever(newcapacity);
            }

            size_t i = 0;
            while(i < len)
            {
                _arr[_size++] = str[i]; 
                ++i;
            }
            _arr[_size] = '\0';
        }
        string& operator+=(const char* str)
        {
            append(str);
            return *this;
        }
        const char* c_str() const
        {
            return _arr;
        }
        //operator
        char& operator[](size_t index)
        {
            assert(index < _size);
            return *(_arr+index);
        }

        size_t find (char c, size_t pos = 0) const
        {
            while(pos < _size)
            {
                if(_arr[pos] == c)
                    return pos;
                pos++;
            }
            return npos;
        }

        private:
        char* _arr;
        size_t _size;
        size_t _capacity;

    };

    ostream& operator<<(ostream& out,const string& s)
    {
        for(const auto &e:s)
            out << e;
        return out;

    }
};


void TestBitstring()
{
    mytest::string s1("hello");
    s1.push_back(' ');
    s1.push_back('b');
    //s1.append(1, 'i');
    //s1.append("acs");
    s1 += "tce";
    s1 += 't';
    //s1.clear();
    cout << s1 << endl;
    cout << s1.size() << endl;
    cout << s1.capacity() << endl;
    // 利用迭代器打印string中的元素
    mytest::string::iterator it = s1.begin();
    while (it != s1.end())
    {
        cout << *it<<" ";
        ++it;
    }
    cout << endl;

    // 这里可以看到一个类只要支持的基本的iterator，就支持范围for
    for(auto ch : s1)
        cout<<ch<<" ";
    cout<<endl;
}


int main()
{
    TestBitstring();
    return 0;
}
