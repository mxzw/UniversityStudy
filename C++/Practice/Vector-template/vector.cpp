#include <iostream>
#include <assert.h>

using namespace std;


namespace mytest{
    template<class _Ty>
    class vector
    {
        public:
            typedef _Ty         value_type;
            typedef value_type* iterator;
            typedef value_type& reference;
            typedef size_t      size_type;
        public:
            iterator begin()const
            {
                return _start;
            }
            iterator end() const
            {
                return _last;
            }
            size_type size()
            {
                return end()-begin();
            }
            size_type capacity()const
            {
                return _end-begin();
            }
            bool empty()const
            {
                return end() == begin();
            }
            reference operator[](size_type n)
            {
               return *(begin() + n); 
            }

        public:
            vector():_start(nullptr),_last(nullptr),_end(nullptr)
            {}
            vector(size_type n,const _Ty& value):_start(nullptr),_last(nullptr),_end(nullptr)
            {
                insert(n,value);
            }
            vector(iterator f,iterator l):_start(nullptr),_last(nullptr),_end(nullptr)
            {
                insert(f,l);
            }   
            vector(const vector<int>& iv)
            {
                reserve(iv.capacity());
                iterator it = begin();
                iterator vit = iv.end();
                while (vit != iv.begin())
                {
                    *it++ = *vit--;     
                }
            }
        public:
            void reserve(size_type n)
            {
                //若 n 的值大于vector的容量，则开辟空间
                //若 n 的值小于等于，则不进行任何操作
                if(n > capacity())
                {
                    //1.新开辟一个空间
                    size_type oldSize = size();
                    _Ty* newVector = new _Ty[n];
                    //2.将原空间的数值赋值到新空间
                    if(_start)
                    {
                        //注意：这里不能使用memcpy,因为memcpy是一个浅拷贝。
                        //memcpy(newVector,_start,sizeof(_Ty)*size());
                        for(size_type i = 0; i < oldSize; ++i)
                        {
                            newVector[i] = _start[i];
                        }
                    }
                    //3.改变三个指针的指向
                    //这里直接重新给三个成员进行赋值，所以调用reserve()函数不用担心迭代器失效的问题
                    _start = newVector;
                    _last = _start + oldSize;
                    _end = _start + n;
                }
            }

            void resize(size_type n,const _Ty& value = _Ty())
            {
                //1.如果n的值小于等于size()的时候，则只需要将_last的指针往前移动即可
                if(n <= size())
                {
                    _last = _start + n;
                    return;
                }
                //2.如果n的值大于capacity()的时候，则需调用reserve()函数，重新设置容量大小
                if(n > capacity())
                {
                    reserve(n);
                }
                //若当n的值大于size()而小于capacity()的时候，只需将_last的指针往后移即可
                
                iterator it = _last;
                _last = _start + n;

                while(it != _last)
                {
                    *it = value;
                    ++it;
                }
                //resize()函数也不需要担心迭代器失效的问题
            }

            void push_back(const _Ty& value)
            {
                insert(end(),value);
            }
            void pop_back()
            {
                erase(end()-1);
            }

            

            iterator insert(iterator pos,const _Ty& value)
            {
                //1.当size()==capacity()时，表明vector已满，再进行插入前需要进行扩容
                if(size()== capacity())
                {
                    size_type oldpos = pos - begin();
                    //这里需要防止一种情况：若vector为空的时候，他的capacity为0，这个时候给他直接扩容2倍是行不通的，因为2*0 = 0，因此就需要进行判断 
                    size_type newcapacity = (capacity() == 0)? 1 : 2*capacity();

                    reserve(newcapacity);

                    //这里空间发生了变化，pos迭代器会失效，因此需要重新对pos进行设置
                    //reserve不会使vector的成员变量失效
                    pos = begin() + oldpos;
                }
                //2.当size() < capacity()时，表明vector未满，插入直接在pos的位置进行插入
                //需要注意的是插入是在pos指向的位置进行插入，并且插入需要挪动数据，将pos位置之后的数据全部向后挪动一个,为防止元素被改写，则需要从后向前进行挪动
                iterator tail = _last;
                while(tail > pos)
                {
                    *tail = *(tail-1);
                    --tail;
                }
                //这里要注意的是挪动数据时，因为没有对pos位置进行操作，所以pos位置的迭代器并没有失效，但是pos位置之后的迭代器全部失效了，但在这里并没有关系，我们并不会用到那些迭代器
               *pos = value;

               //插入完之后，一定要对_last指针+1，因为全部向后挪动了一个元素
               ++_last;

               return pos;
            }

            void insert(size_type n,const _Ty& value)
            {
                for(int i = 0;i < n; ++i)
                {
                    insert(end(),value);
                }
            }
            void insert(iterator f,iterator l)
            {
                while(f!=l)
                {
                    insert(end(),*f);
                    ++f;
                }
            }


            iterator erase(iterator pos)
            {
                assert(pos >= _start || pos < _last);
                //1.删除pos位置的元素，就是将[pos,end()]这个区间向前挪动一个即可
                iterator it = pos + 1;
                while(it != _last)
                {
                    *(it-1) = *(it);
                    ++it;
                }

                --_last;
                return pos;

            }


            

        private:
            iterator _start;
            iterator _last;
            iterator _end;
    };

};

void Test1()
{
    mytest::vector<int> iv;

    cout << "iv.size() = " << iv.size() << endl;
    cout << "iv.capacity() = " << iv.capacity() << endl;
    iv.push_back(1);
    iv.push_back(2);
    iv.push_back(3);
    iv.push_back(4);
    cout << "iv.size() = " << iv.size() << endl;
    cout << "iv.capacity() = " << iv.capacity() << endl;

    mytest::vector<int>::iterator it = iv.begin();

    while(it != iv.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
    iv.pop_back();
    iv.pop_back();
    it = iv.begin();
    while(it != iv.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;


}

void Test2()
{
    mytest::vector<int> iv(10,2); 
    mytest::vector<int>::iterator it = iv.begin();
    while(it != iv.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}

void Test3()
{
    int ar[] = {1,2,3,3,4,5};
    mytest::vector<int> iv(ar,ar+6);
    mytest::vector<int>::iterator it = iv.begin();
    while(it != iv.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;

}
int main()
{
//    Test1();
//    Test2();
    Test3();
    return 0;
}
