#include"SList.h"

//销毁 
////将头指针free掉，然后置空。
void SListDestory(SListNode* phead)
{
    free(phead);
    phead = NULL;
}
//打印
//根据指针的next，一直向后走到空，进行遍历
void SListPrint(SListNode* phead)
{
    SListNode* cur = phead;
    while (cur != NULL)
    {
        printf("%d->", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

//后插
//即申请一个新的节点，然后让原来指针的最后一个指向该节点，然后改节点的next指针指向NULL
//因为是对指针的修改，因此要用二级指针**phead，以下同理。
void SListPushBack(SListNode** phead, SLTDataType x)
{
    SListNode* newnode = BuySListNode(x);

    if (*phead == NULL)
    {
        *phead = newnode;
    }
    else
    {
        //找尾
        SListNode* tail = *phead;
        while (tail->next != NULL)
        {
            tail = tail->next;
        }
        tail->next = newnode;
    }
}

//前插
//将头指针指向新的节点，然后新的节点的next指针指向之前phead->next。
void SListPushFront(SListNode** phead, SLTDataType x)
{
    SListNode* newnode = BuySListNode(x);
    if (*phead == NULL)
    {
        *phead = newnode;
    }
    else
    {
        *phead = newnode;
    }
}


//前删
//将头指针指向phead->next->next，然后free掉phead->next即可（用temp来保存）
void SListPopFront(SListNode** phead)
{
    if (*phead == NULL) //空
    {
        return;
    }
    else if ((*phead)->next == NULL) //一个结点
    {
        free(*phead);
        *phead = NULL;
    }
    else//多个结点
    {
        SListNode* next = (*phead)->next;
        free(*phead);

        *phead = next;
    }
}
//后删
//从头开始遍历，一直到phead->next->next==NULL（倒数第二个节点）,然后让其指向空，再free掉最后一个节点
void SListPopBack(SListNode** phead)
{
    // 链表为空
    if (*phead == NULL)
    {
        return;
    }
    else if ((*phead)->next == NULL) 	// 只有一个节点
    {
        free(*phead);
        *phead = NULL;
    }
    else 	// 多个节点
    {
        SListNode* prev = NULL;
        SListNode* tail = *phead;
        while (tail->next != NULL)
        {
            prev = tail;
            tail = tail->next;
        }

        free(tail);
        tail = NULL;
        prev->next = NULL;
    }
}
//在pos后插入---若要在pos之前插入，对于单链表而言，算法会相对比较复杂，首先需要找到pos之前的位置
//因为单链表没有指向前面的指针，因此就需要在定义一个指针用来存放pos之前的指针，然后再插入元素，再用新插入的节点的next指向pos，即可实现前插。
//而后插相对而言就比较简单，直接到pos位置，然后插入，再完成next指向的变化即可。
void SListInsertAfter(SListNode* pos, SLTDataType x)
{
    SListNode* newnode = BuySListNode(x);
    newnode->next = pos->next;
    pos->next = newnode;
}
//在pos后消除
//消除同插入同理
void SListEraseAfter(SListNode* pos)
{
    if (pos->next == NULL) {
        return;
    }
    SListNode* posNext = pos->next;
    pos->next = posNext->next;
    free(posNext);
    posNext = NULL;
}

    //创建动态的节点
    SListNode* BuySListNode(SLTDataType x)
    {	//申请一个节点
        SListNode* newnode = (SListNode*)malloc(sizeof(SListNode));
        if (newnode == NULL)
        {
            printf("malloc node fail\n");
            exit(-1);
        }

        newnode->data = x;
        newnode->next = NULL;

        return newnode;
    }
    //寻找链表某个元素
    //遍历plist，直到找到x
SListNode* SListFind(SListNode* plist, SLTDataType x)
{
    SListNode* head = plist;
    while (head)
    {
        if (head->data == x)
        {
            return head;
        }
            head = head->next;
        }
    return NULL;
}
