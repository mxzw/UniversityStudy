#include<iostream>
#include<string>
#include <assert.h>
#include <vector>

using namespace std;
template<typename T>
class BST;

template<typename T>
class BSTNode
{
    friend BST<T>;
    public:
    explicit BSTNode() :leftChild_(nullptr), rightChild_(nullptr)
    {}

    BSTNode(T data) : data_(data), leftChild_(nullptr), rightChild_(nullptr)
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
        for (const auto& e : iv)
            insert(root_, e);

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
            return Search(root_, val);

        }
        bool insert(const T& val)
        {
            return insert(root_, val);

        }

        bool remove(const T& val)
        {
            return remove(root_, val);

        }

    protected:
        bool remove(BSTNode<T>*& pos, const T& val)
        {
            if (pos == nullptr)
                return false;
            //首先需要找到需要删除的位置
            BSTNode<T>* cur = pos;
            BSTNode<T>* parent = nullptr;
            while (cur != nullptr && cur->data_ != val)
            {
                parent = cur;
                if (cur->data_ > val)
                    cur = cur->leftChild_;
                else if (cur->data_ < val)
                    cur = cur->rightChild_;
            }

            if (cur == nullptr)
                return false;
            //走到这里说明已经找到了该位置,然后进行删除
            BSTNode<T>* tmp;
            if (cur->leftChild_ && cur->rightChild_)
            {
                parent = cur;
                tmp = cur->leftChild_;
                while (tmp->rightChild_ != nullptr)
                {
                    parent = tmp;
                    tmp = tmp->rightChild_;
                }

                cur->data_ = tmp->data_;

                cur = tmp;
            }

            //if (cur->leftChild_ == nullptr || cur->rightChild_ == nullptr)
            //要删除的节点只有一个子树，或者没有子树

            if (cur->leftChild_ == nullptr)
                tmp = cur->rightChild_;
            else
                tmp = cur->leftChild_;

            if(parent == nullptr)
            {
                delete pos;
                return true;
            }

            //待删除的节点这个时候可能还有子树，我们需将该节点的子树也链接上
            if (parent->data_ > tmp->data_)
                parent->leftChild_ = tmp;
            else
                parent->rightChild_ = tmp;
            delete cur;

            return true;
        }



        BST<T>* Search(BST<T>*& pos, const T& val)
        {
            assert(pos != nullptr);

            if (val == pos->data_)
                return pos;
            else if (pos->data_ > val)
                return Search(pos->leftChild_, val);
            else
                return Search(pos->rightChild_, val);
        }
        T& Min(BSTNode<T>* pos)
        {
            assert(pos != nullptr);

            while (pos->leftChild_)
                pos = pos->leftChild_;

            return pos->data_;
        }
        T& Max(BSTNode<T>* pos)
        {
            assert(pos != nullptr);

            while (pos->rightChild_)
                pos = pos->rightChild_;

            return pos->data_;
        }
        bool insert(BSTNode<T>*& pos, const T& val)
        {
            auto cur = pos;
            BSTNode<T>* parent = nullptr;
            //先找到该插入的位置
            while (cur != nullptr)
            {
                parent = cur;
                if (cur->data_ == val)
                    return false;
                else if (cur->data_ < val)
                    cur = cur->rightChild_;
                else
                    cur = cur->leftChild_;
            }
            //走到这就代表着找到该连接的位置了
            cur = new BSTNode<T>(val);

            //下一步就要进行连接
            if (parent == nullptr)
                pos = cur;
            else
            {
                if (parent->data_ < cur->data_)
                    parent->rightChild_ = cur;
                else if (parent->data_ > cur->data_)
                    parent->leftChild_ = cur;
            }
            return true;
        }

    private:
        BSTNode<T>* root_;
};

void test()
{
    vector<int> iv = { 10, 15,18,12,20,5, 9, 7, 3  };

    BST<int> bst(iv);
    bst.remove(10);
    cout << "dsadadas" << endl;

}

int main()
{
    test();
    return 0;
}

