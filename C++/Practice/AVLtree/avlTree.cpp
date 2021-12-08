#include<iostream>
#include<string>
#include <assert.h>
#include <vector>
#include <stack>

using namespace std;


template<typename T>
class AVLTree;

template<typename T>
class AVLNode {
    friend AVLTree<T>;
    public:
    AVLNode():data_(T()),leftChild_(nullptr),rightChild_(nullptr),bf_(0)
    {}
    AVLNode(const T& val) : data_(val),leftChild_(nullptr),
    rightChild_(nullptr),bf_(0)
    {}
    ~AVLNode()
    {}
    private:
    T data_;
    AVLNode* leftChild_;
    AVLNode* rightChild_;
    //平衡因子
    int bf_;
};


template<typename T>
class AVLTree
{
    public:
        explicit AVLTree():root_(nullptr)
    {}
        AVLTree(vector<T>& iv) : root_(nullptr)
    {
        for (auto& e : iv)
            insert(root_, e);

    }
        bool insert(const T& val)
        {
            return insert(root_, val);

        }
    protected:
        bool insert(AVLNode<T>*& pos, const T& val)
        {
            //首先是像二叉搜索树一样，找到应该插入的位置，并插入
            AVLNode<T>* cur = pos;
            AVLNode<T>* parent = nullptr;

            //栈用来保存插入路径上的节点
            stack<AVLNode<T>*> s;

            //1. 搜索该插入的位置
            while (cur != nullptr)
            {
                parent = cur;
                s.push(parent);
                if (cur->data_ == val)
                    return false;
                else if (cur->data_ < val)
                    cur = cur->rightChild_;
                else
                    cur = cur->leftChild_;
            }
            //1.1 在该位置创建值并进行插入
            cur = new AVLNode<T>(val);
            //如果此时parent为空，则表明该AVL树是一个空树
            if (parent == nullptr)
            {
                pos = cur;
                return true;
            }
            //当parent不为空的时候，则进行链接
            if (parent->data_ < cur->data_)
                parent->rightChild_ = cur;
            else if (parent->data_ > cur->data_)
                parent->leftChild_ = cur;


            //2.插入值可能会引起AVL树的不平衡，我们需要对其进行调整
            /*
             * ①首先我们需要对平衡因子进行修改
             * 我们可以发现当一个值val插入AVL树之后，在寻找适合的插入位置时所走的路径
             * 上的节点的平衡因子均会发生改变，但是我们只需要寻找到第一个失去平衡的节点
             * 即平衡因子的值为-2或2.
             * ②其次我们要根据平衡因子的值来对AVL树进行旋转(左旋、右旋、先左后右和先右后左)
             */

            //2.1 调整平衡因子
            //画图可以发现，当插入在节点的左边的时候，则该节点的平衡因子会 -1
            //当插入在节点的右边的时候，该节点的平衡因子会 +1
            //该规则包括了插入路径中的所有节点均是如此，这些节点的平衡因子均会发生变化
            //因此，我们只需要对回溯上来的第一次失衡节点进行调整

            //那么该如何实现这条路径上节点的平衡因子的计算呢？我们使用一个栈的结构来对这些节点进行保存

            while (!s.empty())
            {
                parent = s.top();
                s.pop();
                //此时cur是指向插入的节点的
                //若在节点的左边，则平衡因子减1，若在右，则加1
                if (cur == parent->leftChild_)
                    --parent->bf_;
                else
                    ++parent->bf_;

                if (parent->bf_ == 0)
                {
                    //若此时该节点的平衡因子为0，则说明插入的节点在该AVL树中已经达到平衡，换个角度想想的话，如果原来的节点的平衡因子为 -1 或 1，这也就说明该节点（-1）没有右子树或(1)没有左子树，当该插入的值插入到该节点的右子树或左子树的时候，刚好平衡了该节点的平衡因子，其值就变为0，从整个树的角度上来看的话，插入的值并没有使树的高度变高，因此，在这种情况下我们是不需要进行修改和调整的
                    break;
                }
                else if (parent->bf_ == -1 || parent->bf_ == 1)
                {
                    //当平衡因子为-1或1 的时候，证明原来该节点的平衡因子是0，这种情况有可能是没有左右子树，或者左右子树高度相等；但是当新的节点插入进来后，该节点的平衡因子就会变为-1或1，而纵观整个AVL树，它的高度肯定发生了变化，高度发生了变化则有可能会造成AVL树失衡，因此，这种情况下，我们需要回溯，回溯到上一个节点的值，判断上一个节点的平衡因子。
                    cur = parent;
                }
                else
                {
                    //这种情况就是当我们新的节点插入的时候，造成了AVL树的失衡，这种的值一般均是-2或2，在这种情况下，我们就需要对该节点进行相应的调整(单旋转和双旋转)

                    /* 
                     * 众所周知，AVL失衡之后对其调整有四种办法：
                     * ① / ：左低右高，调整方法为右旋转
                     * ② \ ：左高右低，调整方法为左旋转
                     * ③ > ：形状像右胳膊，因此调整方法为先右后左旋转( 先右：'>' => '\'，
                     后左：'\'=>‘∩' )
                     * ④ <：形状像左胳膊，因此调整方法为先左后右旋转（ 先左：'<' => '/'
                     后右：'/' =>‘∩')
                     * 那么该如何对其进行判断呢？因为我们不知道当该节点失衡之后，它应该采取何种策略进行调整?s
                     * 答案是平衡因子的符号
                     * a. 若父节点和子节点的符号均为负数，则标明它是 '/' 
                     * b. 若父节点和子节点的符号均为正数，则表明它是 '\'
                     * c. 若父节点为负数，子节点为正数，则表明它是   '<'
                     * d. 若父节点为正数，子节点为负数，则表明它是  '>'
                     */
                    if (parent->bf_ < 0)
                    {
                        if (cur->bf_ < 0)
                        {
                            // 表明为：'/'，应该使用右旋转
                            rotateR(parent);
                        }
                        else
                        {
                            //表明为：'<'，则应该使用先左后右旋转
                            rotateLR(parent);
                        }
                    }
                    else
                    {
                        if (cur->bf_ > 0)
                        {
                            //表明为：'\'，则应该使用左旋转
                            rotateL(parent);
                        }
                        else
                        {
                            //表明为：'>'，则应该使用先右后左旋转
                            rotateRL(parent);
                        }
                    }
                    break;
                }
            }

            //当栈为空的时候，说明整个树都被调了一遍
            if(s.empty())
                pos = parent;
            else {
                //当栈不为空的时候，说明只对树中的某个子结构进行了调整，我们要进行相应的链接
                AVLNode<T>* tmp = s.top();
                //此时tmp为parent的父节点，但是为了知道parent位于tmp的哪个位置，则需要进行判断
                if (tmp->data_ < parent->data_)
                {
                    tmp->rightChild_ = parent;
                }
                else if (tmp->data_ > parent->data_)
                {
                    tmp->leftChild_ = parent;
                }
            }

            return true;

        }
    protected:
        // '\'：左旋转调整方法
        void rotateL(AVLNode<T>*& ptr)
        {
            //1.调整AVL树结构
            AVLNode<T>* subL = ptr;
            ptr = subL->rightChild_;

            //将待父节点的右指针指向其右子树的右节点
            subL->rightChild_ = ptr->leftChild_;
            //再让右子节点的左指针指向父节点，这样就能将其调至平衡,其该节点就为新的节点
            ptr->leftChild_ = subL;

            //2.调整平衡因子
            //此处调整的是刚刚修改了的两个节点，即ptr和subL
            //在调整之前我们一定要知道父节点的平衡因子为2，但是在经过左旋转之后
            //不管右子节点的右子树是否有值，再调整完成之后，其平衡因子一定为0
            ptr->bf_ = subL->bf_ = 0;
        }

        // '/'：右单旋转
        void rotateR(AVLNode<T>*& ptr)
        {
            AVLNode<T>* subR = ptr;
            ptr = subR->leftChild_;

            subR->leftChild_ = ptr->rightChild_;
            ptr->rightChild_ = subR;

            ptr->bf_ = subR->bf_ = 0;
        }

        // '>'：先右旋再左旋
        void rotateRL(AVLNode<T>*& ptr)
        {
            //我们需要经过两次旋转
            //1. 右旋，调整平衡因子

            //首先根据插入路径来确定平衡后根的位置
            AVLNode<T>* subL = ptr;
            AVLNode<T>* subR = ptr->rightChild_;
            ptr = subR->leftChild_;

            //1.1 右旋
            subR->leftChild_ = ptr->rightChild_;
            ptr->rightChild_ = subR;

            //注意这里没有链接subL 和 ptr ，它们之间的链接现在是断开的

            //1.2 调整右旋的平衡因子
            //这里需要注意的是，再右旋完毕之后，该AVL树还没有平衡，所以调节平衡因子的时候，要分情况来看
            //当ptr在调整之前的平衡因子为 1 或 0的时候，则 subR的平衡因子为 0，(可以举例验证)
            //当 prt 为 -1 的时候，则subR的平衡因子为 1 
            if (ptr->bf_ >= 0)
                subR->bf_ = 0;
            else
                subR->bf_ = 1;

            //2. 左旋，调整平衡因子
            //2.1 左旋
            subL->rightChild_ = ptr->leftChild_;
            ptr->leftChild_ = subL;

            //2.2 调整左旋的平衡因子
            if (ptr->bf_ == 1)
                subL->bf_ = -1;
            else
                subL->bf_ = 0;

            //调整完之后，ptr所指的树就为一个AVL树，因此平衡因子为0
            //为什么会是0呢？理由很简单，因为每当新插入一个节点，当不平衡时(-2或2)，就需要进行旋转调整，再调整之后，必然不平衡的节点处的平衡因子为0，因为每次就只有那一个节点导致了不平衡，我们要做的就是将其调整至左右平衡。
            ptr->bf_ = 0;
        }

        //'<'：先左旋再右旋
        void rotateLR(AVLNode<T>*& ptr)
        {
            AVLNode<T>* subR = ptr;
            AVLNode<T>* subL = ptr->leftChild_;
            ptr = subL->rightChild_;

            //左旋并调整
            subL->rightChild_ = ptr->leftChild_;
            ptr->leftChild_ = subL;

            //当ptr->bf_的绝对值为1的时候，则subL的左树上必然有一个节点
            //当ptr->bf_的绝对值为0的时候，则subL的左树上必然没有节点

            if (ptr->bf_ <= 0)
                subL->bf_ = 0;
            else
                subL->bf_ = -1;

            //右旋并调整
            subR->leftChild_ = ptr->rightChild_;
            ptr->rightChild_ = subR;

            if (ptr->bf_ >= 0)
                subR->bf_ = 0;
            else
                subR->bf_ = 1;

            ptr->bf_ = 0;
        }

    private:
        AVLNode<T>* root_;
};

void test()
{
    vector<int> iv = { 16,3,7,11,9,26,18,14,15  };
    AVLTree<int> avl(iv);
    cout << endl;
}

int main()
{
    test();
    return 0;
}
