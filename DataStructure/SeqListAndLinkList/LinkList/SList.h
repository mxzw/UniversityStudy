#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef int SLTDataType;

typedef struct SListNode
{
    SLTDataType data;
    struct SListNode* next;

}SListNode;

//销毁
void SListDestory(SListNode* phead);
////打印
void SListPrint(SListNode* phead);
//
////后插
void SListPushBack(SListNode** phead, SLTDataType x);
////前插
void SListPushFront(SListNode** phead, SLTDataType x);
////前删
void SListPopFront(SListNode** phead);
////后删
void SListPopBack(SListNode** phead);

////在pos后插入
void SListInsertAfter(SListNode* pos, SLTDataType x);
////在pos后消除
void SListEraseAfter(SListNode* pos);


////创建动态的节点
SListNode* BuySListNode(SLTDataType x);
////寻找链表某个元素
SListNode* SListFind(SListNode* plist, SLTDataType x);
