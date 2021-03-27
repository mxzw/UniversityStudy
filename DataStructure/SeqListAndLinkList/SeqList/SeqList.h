#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

#define N 100
typedef int SeqDataType;

//顺序表：数组中存储的数据是连续存储的
//静态的顺序表(存储数据的空间是固定的)
//问题：开小了不够用，开大了，浪费空间，现实中不实用
/*typedef struct SeqList
  {
  int a[N];
  int size;
  }SeqList;*/

//动态的顺序表(存储数据的空间是可以动态增长的，可以更好的适应现实使用)
typedef struct SeqList
{
    SeqDataType* a;//存储数据空间的指针
    int size;//有效数据个数
    int capacity;//容量
}seqList;

void SeqListInit(seqList* s1 );
void SeqListDestroy(seqList* s1 );

void SeqListPushBack(seqList* s1,SeqDataType x);
void SeqListPushFront(seqList* s1,SeqDataType x);
void SeqListPopFront(seqList* s1);
void SeqListPopBack(seqList* s1);
void SeqListPrint(seqList* s1);
void CheckCapacity(seqList* s1);
void SeqListInsert(seqList* s1,int pos,SeqDataType x);
void SeqListErase(seqList* s1,int pos);
int  SeqListFind(seqList* s,SeqDataType x);
