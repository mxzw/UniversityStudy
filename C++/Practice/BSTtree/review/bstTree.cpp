#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;


template<typename T>
class bstTree;

template<typename T>
class bstNode
{
    friend bstTree<T>; 

    public:
    bstNode():left_(nullptr),right_(nullptr)
    {}
    bstNode(T value) : val_(value),left_(nullptr),right_(nullptr)
    {}
    private:
    T val_;
    bstNode* left_;
    bstNode* right_;
};

template<typename T>
class bstTree
{
    public:
        bstTree():root_(nullptr)
        {}

        ~bstTree()
        { }

    public:
        bool Insert(T value)
        {
            return _Insert(root_,value);
        }
        bool Remove(T value)
        {
            return _Remove(root_,value);
        }
        T Max()
        {
            assert(root_);
            bstNode<T>* cur = root_;
            while(cur->right_)
                cur = cur->right_;

            return cur->val_;
        }
        T Min()
        {
            assert(root_);
            bstNode<T>* cur = root_;
            while(cur->left_)
                cur = cur->left_;

            return cur->val_;
        }
    public:
        void Print()
        {
            assert(root_ != nullptr);
            queue<bstNode<T>*> bq;
            bq.push(root_);
            while(!bq.empty())
            {
                bstNode<T>* cur = bq.front();
                bq.pop();

                cout << cur->val_ << " ";

                if(cur->left_)
                    bq.push(cur->left_);

                if(cur->right_)
                    bq.push(cur->right_);
            }
            cout << endl;
        }
    protected:
        bool _Insert(bstNode<T>*& pos,T value);
        bool _Remove(bstNode<T>*& pos,T value);
    private:
        bstNode<T>* root_;
};

template<typename T>
bool bstTree<T>::_Remove(bstNode<T>*& pos,T value)
{
    if(pos == nullptr)
        return false;
    bstNode<T>* cur = pos;
    bstNode<T>* parent = nullptr;
    while(cur && cur->val_ != value)
    {
        parent = cur;
        if(cur->val_ > value)
            cur = cur->left_;
        else
            cur = cur->right_;
    }

    if(cur == nullptr)
        return false;

    bstNode<T>* tmp;

    if(cur->left_ && cur->right_)
    {
        parent = cur;

        tmp = cur->left_;

        while(tmp->right_)
        {
            parent = tmp;
            tmp = tmp->right_;
        }

        cur->val_ = tmp->val_;

        cur = tmp;
    }

    if(cur->left_ == nullptr && cur->right_ == nullptr)
    {
        if(parent->val_ > cur->val_)
            parent->left_ = nullptr;
        else
            parent->right_ = nullptr;

        delete cur;
        return true;
    }

    if(cur->left_ != nullptr)
        tmp = cur->left_;
    else
        tmp = cur->right_;

    if(parent == nullptr)
    {
        delete pos;
        return true;
    }

    if(parent->val_ > tmp->val_)
        parent->left_ = tmp;
    else
        parent->right_ = tmp;

    delete cur;

    return true;
}

template<typename T>
bool bstTree<T>::_Insert(bstNode<T>*& pos,T value)
{
    bstNode<T>* cur = pos;
    bstNode<T>* parent = nullptr;

    while(cur)
    {
        parent = cur;
        if(cur->val_ == value)
            return false;
        if(cur->val_ < value)
            cur = cur->right_;
        else 
            cur = cur->left_;
    }

    cur = new bstNode<T>(value);
    if(parent == nullptr)
        pos = cur;
    else
    {
        if(parent->val_ > value)
            parent->left_ = cur;
        else
            parent->right_ = cur;
    }

    return true;

}


void test()
{  
    vector<int> iv = {2,1,3,0,4,5};
    bstTree<int> bt;
    for(const auto &e : iv)
        bt.Insert(e);
    bt.Print();
   /* bt.Remove(2);
    bt.Print();
    cout << bt.Max() << endl;
    cout << bt.Min() << endl;
    */

    for(const auto &e : iv)
        bt.Remove(e);
}

int main()
{
    test();
    return 0;
}
