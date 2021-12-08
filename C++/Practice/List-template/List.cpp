#include <iostream>
#include <cstdlib>

using namespace std;


namespace bit
{
    template <class _Ty>
        class List{
            protected:
                typedef size_t _Size;
                struct _Node;
                typedef _Node* _Nodeptr;
                struct _Node
                {
                    _Nodeptr _Next,_Prev;
                    _Ty value;
                };
                struct _ACC
                {
                    typedef _Node*& _Nodepref;
                    typedef _Ty& _Vref; 
                    static _Nodepref _Next(_Nodeptr _S)
                    {
                        return _S->_Next;
                    }
                    static _Nodepref _Prev(_Nodeptr _S)
                    {
                        return _S->_Prev;
                    }
                    static _Vref _Value(_Nodeptr _S)
                    {
                        return _S->value;
                    }
                };

                _Nodeptr  _BuyListNode(_Nodeptr Narg = 0,_Nodeptr Parg = 0)
                {
                    _Nodeptr _S = (_Nodeptr) malloc(sizeof(_Node));
                    _ACC::_Next(_S) = Narg != 0 ? Narg : _S;
                    _ACC::_Prev(_S) = Parg != 0 ? Parg : _S;
                    return _S;
                }

                void _FreeNode(_Nodeptr _S)
                {
                    free(_S);
                }

            public:
                class iterator
                {
                    public:
                        iterator()
                        {
                            cout << "Over create iterator!" << endl;
                        }
                        iterator(_Nodeptr ptr) : _Ptr(ptr)
                    {}
                        iterator(const iterator &_it)
                        {
                            this->_Ptr = _it._Ptr;
                        }

                        bool operator!=(iterator& _it) const
                        {
                            return _Ptr != _it._Ptr;
                        }
                        bool operator==(iterator& _it) const
                        {
                            return!(*this!=_it);
                        }
                        iterator& operator++()
                        {
                            _Ptr = _ACC::_Next(_Ptr);
                            return *this;
                        }
                        iterator operator++(int)
                        {
                            iterator tmp(*this);
                            ++(*this);
                            return tmp;
                        }
                        _Ty operator*()
                        {
                            return _ACC::_Value(_Ptr);
                        }
                        iterator& operator--()
                        {
                            _Ptr = _ACC::_Prev(_Ptr);
                            return *this;
                        }
                        iterator operator--(int)
                        {
                            iterator tmp(*this);
                            --(*this);
                            return tmp;
                        }
                        _Nodeptr _MyNode()
                        {
                            return _Ptr;
                        }

                    private:
                        _Nodeptr _Ptr;
                };

            public:
                explicit List():Head(_BuyListNode()),_size(0)
            {
                _ACC::_Next(Head) = Head;
                _ACC::_Prev(Head) = Head;
                cout << "Over create List<class _Ty>" << endl;
            } 
                List(_Size _n,const _Ty& _V = _Ty() ):Head(_BuyListNode()),_size(0)
            {
                insert(begin(),_n,_V);
            }
                List(const _Ty* _f,const _Ty* _l):Head(_BuyListNode()),_size(0)
            {
                insert(begin(),_f,_l);
            }
                ~List()
                {
                    clear();
                    _FreeNode(Head);
                    Head=0,_size=0;
                }
            public:
                _Size size() const
                {
                    return _size;
                }
                bool empty()const
                {
                    return _size==0;
                }
                _Ty& front()
                {
                    return *begin();
                }
                const _Ty& front() const
                {
                    return *begin();
                }
                _Ty& back()
                {
                    return *(--end());
                }

                void push_back(const _Ty& _val)
                {
                    insert(end(),_val);
                }
                void push_front(const _Ty& _val)
                {
                    insert(begin(),_val);
                }
                /*
                   void push_back(_Ty val)
                   {
                   _Nodeptr _tmp = _BuyListNode(Head,Head->_Prev); 
                   _ACC::_Value(_tmp) = val;
                   _ACC::_Prev(_ACC::_Next(_tmp)) = _tmp;
                   _ACC::_Next(_ACC::_Prev(_tmp)) = _tmp;

                   size++;
                   cout << "push_back access" << endl;
                   }
                   */

                iterator begin()const
                {
                    return iterator(_ACC::_Next(Head));
                }
                iterator end() const
                {
                    return iterator(Head);
                }
                iterator insert(iterator _it,_Ty val= _Ty())
                {
                    _Nodeptr _S = _it._MyNode();
                    _ACC::_Prev(_S) = _BuyListNode(_S,_ACC::_Prev(_S));
                    _S = _ACC::_Prev(_S);

                    _ACC::_Value(_S) = val;
                    _ACC::_Next(_ACC::_Prev(_S)) = _S;
                    ++_size;
                    cout << "iterator insert success!" << endl;
                    return iterator(_S);
                }
                iterator erase(iterator _it)
                {
                    _Nodeptr _S = (_it++)._MyNode();
                    _ACC::_Next(_ACC::_Prev(_S)) = _ACC::_Next(_S);
                    _ACC::_Prev(_ACC::_Next(_S)) = _ACC::_Prev(_S);

                    --_size;
                    _FreeNode(_S);
                    return _it;
                }

                void insert(iterator _it,_Size _M,const _Ty& _x)
                {
                    for(;0 < _M; --_M)
                        insert(_it,_x);
                }
                void insert(iterator _it,const _Ty*  _f,const _Ty* _l)
                {
                    while(_f!=_l)
                    {
                        insert(_it,*_f++);
                    }
                }
                iterator erase(iterator _itbegin, iterator _itend)
                {
                    while(_itbegin != _itend)
                    {
                        erase(_itbegin++);
                    }
                    return _itbegin;
                }
                void clear()
                {
                    erase(begin(),end());
                }




            private:        
                _Nodeptr Head;
                _Size _size;

        };
}

void test1()
{
    bit::List<int> mylist;
    mylist.push_back(1);
    mylist.push_back(2);
}

void test2()
{
    bit::List<int> mylist;
    mylist.push_back(1);
    mylist.push_back(2);
    bit::List<int>::iterator it1 = mylist.begin();
    bit::List<int>::iterator it2 = mylist.end();

    while(it1 != it2)
    {
        cout << *it1 << "->";
        ++it1;
    }

    cout << "over print to iterator!" << endl;
}

void test3()
{
    int ar[] = {1,2,3,4,5,6,7,8,9,10};
    bit::List<int> mylist(ar, ar+10);

    //mylist.erase(mylist.begin(), mylist.end()); //[  )
//    mylist.clear();

    bit::List<int>::iterator it = mylist.begin();
    bit::List<int>::iterator it1 = mylist.end();
    while(it != it1)
    {
        cout<<*it<<"-->";
        ++it; //it++
    }
    cout<<"Over."<<endl;
}


int main()
{
    //test1();
    //test2();
    test3();

    return 0;
}
