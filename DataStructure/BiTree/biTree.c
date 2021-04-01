#include "biTree.h"


// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树
BTNode* BinaryTreeCreate(BTDataType* a, int n, int* pi)
{
    //pi是作为数组当前的指针，n是数组a的总长度
    //若数组的值为 # 或当pi的值大于数组的长度，说明当前节点为空
    if(a[*pi] == '#' || *pi >= n)
    {
        printf("NULL ");
        (*pi)++;
        return NULL;
    }

    BTNode* dst = (BTNode*)malloc(sizeof(BTNode));
    dst->_data = a[*pi];
    printf("%c ",dst->_data);
    (*pi)++;

    dst->_left = BinaryTreeCreate(a,n,pi);
    dst->_right = BinaryTreeCreate(a,n,pi);

    return dst;

}
// 二叉树销毁
void BinaryTreeDestory(BTNode** root)
{
    if(*root==NULL)
    {
        return;
    }
    BTNode* tmp = *root;
    free(*root);

    BinaryTreeDestory(&(tmp->_left));
    BinaryTreeDestory(&(tmp->_right));


}
// 二叉树节点个数
int BinaryTreeSize(BTNode* root)
{
    if(root == NULL)
    {
        return 0;
    }
    return 1+BinaryTreeSize(root->_left)+BinaryTreeSize(root->_right); 
}
// 二叉树叶子节点个数
int BinaryTreeLeafSize(BTNode* root)
{
    if(root==NULL)
    {
        return 0;
    }
    //若左节点为空，右结点不为空，则证明有一个叶子节点
    ///只有当左节点为空，右结点不为空时，即为特殊情况
    //当左节点不为空的时候，正常遍历左节点的左右子树
    if(root->_left == NULL && root->_right)
    {
        return 1;
    }

    return BinaryTreeLeafSize(root->_left) + BinaryTreeLeafSize(root->_right);

}
// 二叉树第k层节点个数
int BinaryTreeLevelKSize(BTNode* root, int k)
{
    //根节点第三层的节点个数等于第二层节点左右孩子个数之和
    //第二层节点的个数为第一层所有节点个数之和（根节点）
    if(root==NULL)
    {
        return 0;
    }
    if(k==1)
    {
        return 1;
    }

    return BinaryTreeLevelKSize(root->_left,k-1) + BinaryTreeLevelKSize(root->_right,k-1);
}
// 二叉树查找值为x的节点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
    if(root==NULL)
    {
        return NULL;
    }
    if(root->_data == x)
    {
        return root;
    }
    BTNode* ret = BinaryTreeFind(root->_left,x); 
    //若ret不为空，则表明找到了
    if(ret!=NULL)
    {
        return ret;
    }

    ret = BinaryTreeFind(root->_right,x);
    if(ret != NULL)
    {
        return ret;
    }
    return NULL;
}
// 二叉树前序遍历 
void BinaryTreePrevOrder(BTNode* root)
{
    if(root == NULL)
    {
        return;
    }

    printf("%c ",root->_data);

    BinaryTreePrevOrder(root->_left);
    BinaryTreePrevOrder(root->_right);
}

// 二叉树中序遍历
void BinaryTreeInOrder(BTNode* root)
{
    if(root == NULL)
    {
        return;
    }
    BinaryTreeInOrder(root->_left);
    printf("%c ",root->_data);
    BinaryTreeInOrder(root->_right);
}
// 二叉树后序遍历
void BinaryTreePostOrder(BTNode* root)
{
    if(root==NULL)
    {
        return;
    }
    BinaryTreePostOrder(root->_left);
    BinaryTreePostOrder(root->_right);
    printf("%c ",root->_data);
}
// 层序遍历
void BinaryTreeLevelOrder(BTNode* root)
{
    //首先将根节点入队，再将根结点入队的同时，将根结点的左右孩子入队，然后一直递归下去，注意这里需要入队的是该节点，而不是该节点的值，因为该节点保存有其对应的左右子树的指针
    Queue q;
    QueueInit(&q);

    if(root)
    {
        QueuePush(&q,root);
    }

    //这里判断是否遍历完树的依据是队列是否为空，当队列为不为空时，说明还有节点没有遍历完
    while(!QueueEmpty(&q))
    {
        //定义一个临时变量来存放该节点
        BTNode* tmp = QueueFront(&q);
        printf("%c ",tmp->_data);

        if(tmp->_left)
        {
            QueuePush(&q,tmp->_left);
        }
        if(tmp->_right)
        {
            QueuePush(&q,tmp->_right);
        }
        QueuePop(&q);
    }
    QueueDestroy(&q);
}
// 判断二叉树是否是完全二叉树
int BinaryTreeComplete(BTNode* root)
{
    //根据队列中的入的空来判断，如果遇到空，若后面全为连续的空，则证明是完全二叉树，若不是连续的空，则证明不是完全二叉树
    //完全二叉树：1.前n-1层是满的 2.最后一层的节点是连续的
    Queue q;
    QueueInit(&q);

    //若root不为空，则插入到队列中
    if(root)
    {
        QueuePush(&q,root);
    }

    while(!QueueEmpty(&q))
    {
        BTNode* front = QueueFront(&q);
        QueuePop(&q);
        //若当前节点为空，则直接跳出
        if(front == NULL)
        {
            break;
        }
        QueuePush(&q,front->_left);
        QueuePush(&q,front->_right);
    }
    while(!QueueEmpty(&q))
    {
        BTNode* front = QueueFront(&q);
        QueuePop(&q);
        //若遇到空之后，后面还有非空，则就不是完全二叉树
        if(front != NULL)
        {
            return 0;
        }

    }
    return 1;


}
