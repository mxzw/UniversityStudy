#include "TList.h"


//创建一个双向链表的结点
ListNode* BuyListNode(LTDataType x){
    ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
    newnode->data = x;
    newnode->next = NULL;
    newnode->prev = NULL;

    return newnode;

}
// 创建返回链表的头结点.      
ListNode* ListInit(){
    ListNode* phead = (ListNode*)malloc(sizeof(ListNode));
    phead->next = phead;
    phead->prev = phead;
    
    return phead;
}
// 双向链表销毁      
void ListDestory(ListNode* plist){
    free(plist);
    plist = NULL;
}
// 双向链表打印      
void ListPrint(ListNode* plist){
    assert(plist);

    ListNode* cur = plist->next;
    while(cur != plist)
    {
        printf("%d ",cur->data);
        cur = cur->next;
    }
    printf("\n");
}

// 双向链表尾插      
void ListPushBack(ListNode* plist, LTDataType x){
    assert(plist);

    ListNode* tail = plist->prev;
    ListNode* newnode = BuyListNode(x);
    //尾的下一个指向新结点，新结点的前一个指向尾，新结点的下一个指向头，头结点的前一个指向新结点
    tail->next = newnode;
    newnode->prev = tail;
    newnode->next = plist;
    plist->prev = newnode;

    //第二种方式实现尾插
    //ListInsert(plist,x);
}
// 双向链表尾删      
void ListPopBack(ListNode* plist){
    assert(plist);
    ListNode* tail = plist->prev;
    ListNode* tailPrev = tail->prev;
    //如果最后一个数据删完以后，链表恢复到最开始状态，只有头结点，并且是循环状态
    free(tail);
    tailPrev->next = plist;
    plist->prev = tailPrev;

    //第二种方式实现尾删
    //ListErase(plist->prev);
}
//双向链表头插    
void ListPushFront(ListNode* plist, LTDataType x){
    assert(plist);
    ListNode* newnode = BuyListNode(x);
    ListNode* next = plist->next;

    plist->next = newnode;
    newnode->prev = plist;
    newnode->next = next;
    next->prev = newnode;

    //第二种方式实现头插
    //ListInsert(plist->next,x);
}
// 双向链表头删    
void ListPopFront(ListNode* plist){
    assert(plist);
    //若无数据，则不删除
    assert(plist->prev!=plist);

    ListNode* popNode = plist->next;
    ListNode* next = popNode->next;
    free(popNode);

    plist->next = next;
    next->prev = plist;

    //第二种方式实现头删
    //ListErase(plist->next);
}

// 双向链表查找 pos之前插入                             
void ListInsert(ListNode* pos, LTDataType x){
    assert(pos);
    ListNode* newnode = BuyListNode(x);
    ListNode* posPrev = pos->prev;

    posPrev->next = newnode;
    newnode->prev = posPrev;
    newnode->next = pos;
    pos->prev = newnode;

}
// 双向链表删除pos位置的节点       
void ListErase(ListNode* pos){
    assert(pos);
    ListNode* posPrev = pos->prev;
    ListNode* posNext = pos->next;

    free(pos);
    posPrev->next = posNext;
    posNext->prev = posPrev;
}
