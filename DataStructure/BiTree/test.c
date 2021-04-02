#include "biTree.h"

int main()
{
    char a[] = "ABD##E#H##CF##G##";
    int i = 0;
    BTNode* cur = BinaryTreeCreate(a,17,&i);
    printf("\n");

    int t = BinaryTreeSize(cur);
    printf("二叉树的大小：%d\n",t);

    printf("二叉树叶子节点的个数：%d\n",BinaryTreeLeafSize(cur));

    printf("二叉树第k层节点个数：%d\n",BinaryTreeLevelKSize(cur,3));

    printf("寻找值为：%c的数\n",BinaryTreeFind(cur,'G')->_data);

    printf("前序遍历：");
    BinaryTreePrevOrder(cur);
    printf("\n");

    printf("后序遍历：");
    BinaryTreePostOrder(cur);
    printf("\n");

    printf("中序遍历：");
    BinaryTreeInOrder(cur);
    printf("\n");

    printf("层序遍历：");
    BinaryTreeLevelOrder(cur);
    printf("\n");

    printf("是否为完全二叉树：%d\n",BinaryTreeComplete(cur));

    BinaryTreeDestory(&cur);
    printf("Destory Successly\n");
}
