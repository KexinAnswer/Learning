#include "SeqList.h"

void TestSeqList1() {
	SeqList seqlist;

	SeqListInit(&seqlist, 100);

	SeqListPushBack(&seqlist, 1);
	SeqListPushBack(&seqlist, 2);
	SeqListPushBack(&seqlist, 3);
	// 1, 2, 3
	SeqListPrint(&seqlist);
	SeqListPushFront(&seqlist, 11);
	SeqListPushFront(&seqlist, 12);
	SeqListPushFront(&seqlist, 13);
	// 13, 12, 11, 1, 2, 3
	SeqListPrint(&seqlist);

	SeqListInsert(&seqlist, 4, 100);
	// 13, 12, 11, 1, 100, 2, 3
	SeqListPrint(&seqlist);


	SeqListPopBack(&seqlist);
	// 13, 12, 11, 1, 100, 2
	SeqListPrint(&seqlist);

	SeqListPopFront(&seqlist);
	// 12, 11, 1, 100, 2
	SeqListPrint(&seqlist);

	SeqListErase(&seqlist, 2);
	// 12, 11, 100, 2
	SeqListPrint(&seqlist);

	SeqListDestroy(&seqlist);
}

int main() {
	TestSeqList1();

	system("pause");
	return 0;
}