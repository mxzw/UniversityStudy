#include <iostream>
#include <assert.h>
#include <vector>

using namespace std;

template<typename T>
class BSTNode
{
    public:
        explicit BSTNode():leftChild_(nullptr),rightChild_(nullptr)
    {}

        BSTNode(T data) : data_(data),leftChild_(nullptr),rightChild_(nullptr)
    {}

        ~BSTNode() {}

    private:
        T data_;
        BSTNode* leftChild_;
        BSTNode* rightChild_;
};

template<typename T>
class BST
{
    public:
        BST() : root_(nullptr)
        {}
        BST(vector<T> iv) : root_(nullptr)
        {
            for(const auto &e : iv)
                insert(root_,e);
        }
        ~BST() {}
        T& Max() const
        {
            return Max(root_);
        }

        T& Min() const
        {
            return Min(root_);
        }

        BST<T>* Search(const T& val) const
        {
            return Search(root_,val);
        }
        bool insert(const T& val)
        {
            return insert(root_,val);
        }

        bool remove(const T& val)
        {
            return remove(root_,val);
        }

    protected:
        bool remove(BST<T>*& pos,const T& val)
        {
            if(pos == nullptr)
                return false;
            else if(pos->data_ < val)
                return remove(pos->rightChild_,val);
            else if(pos->data_ > val)
                return remove(pos->leftChild_,val);
            else
            {
                if(pos->leftChild_ && pos->rightChild_)
                {
                     auto tmp = pos->leftChild_;
                     while(tmp->rightChild_ != nullptr)
                         tmp = tmp->rightChild_;
                     pos->data_ = tmp->data_;
                     remove(pos->leftChild_,pos->data_);
                }
                else
                {
                    auto tmp = pos;
                    if(pos->leftChild_ != nullptr)
                        pos = pos->leftChild_;
                    else
                        pos = pos->rightChild_;

                    delete tmp;
                    return true;
                }


            }

        }
        BST<T>* Search(BST<T>*& pos,const T& val)
        {
            assert(pos != nullptr);

            if(val == pos->data_)
                return pos;
            else if(pos->data_ > val)
                return Search(pos->leftChild_,val);
            else
                return Search(pos->rightChild_,val);
        }
        T& Min(BSTNode<T>* pos)
        {
            assert(pos != nullptr);

            while(pos->leftChild_)
                pos = pos->leftChild_;

            return pos->data_;
        }
        T& Max(BSTNode<T>* pos)
        {
            assert(pos != nullptr);

            while(pos->rightChild_)
                pos = pos->rightChild_;

            return pos->data_;
        }
        bool insert(BSTNode<T>*& pos,const T& val)
        {
            if(pos == nullptr)
            {
                pos = new BSTNode<T>(val);
                return true;
            }

            if(pos->data_ > pos)
                insert(pos->leftChild_,val);
            else if(pos->data_ < pos)
                insert(pos->rightChild_,val);

            return false;
        }



    private: 
        BSTNode<T>* root_; 
};


int main()
{

    return 0;
}
