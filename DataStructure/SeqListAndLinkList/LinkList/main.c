nclude "SList.h"

void SListTest1()
{
	SListNode* phead = NULL;  // 空链表
	SListPushBack(&phead, 1);
	SListPushBack(&phead, 2);
	SListPushBack(&phead, 3);
	SListPushBack(&phead, 4);
	SListPushBack(&phead, 5);

	SListPrint(phead);

	SListPushFront(&phead, 0);
	SListPushFront(&phead, -1);
	SListPrint(phead);

	SListPopBack(&phead);
	SListPopBack(&phead);
	SListPopBack(&phead);
	SListPopBack(&phead);
	SListPopBack(&phead);
	SListPopBack(&phead);
	SListPopBack(&phead);
	SListPopBack(&phead);
	SListPrint(phead);

	SListPushFront(&phead, 1);
	SListPushFront(&phead, 2);
	SListPushFront(&phead, 3);
	SListPushFront(&phead, 4);
	SListPrint(phead);

	SListPopFront(&phead);
	SListPopFront(&phead);
	SListPrint(phead);

	SListPopFront(&phead);
	SListPopFront(&phead);
	SListPopFront(&phead);
	SListPrint(phead);
}

int main()
{
	SListTest1();

	return 0;
}
