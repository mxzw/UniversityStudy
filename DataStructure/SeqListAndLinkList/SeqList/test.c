#include "SeqList.h"

int main()
{
  seqList s1;
  SeqListInit(&s1);
  SeqListPushBack(&s1,1);
  SeqListPushBack(&s1,2);
  SeqListPushBack(&s1,3);
  SeqListPushBack(&s1,4);
  SeqListPushBack(&s1,5);
  SeqListPushBack(&s1,6);
  SeqListPrint(&s1);

  SeqListPushFront(&s1,0);
  SeqListPrint(&s1);

  SeqListDestroy(&s1);
  
  return 0;
}
