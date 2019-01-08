//顺序表头插
#include <stdio.h>
#include <malloc.h>
struct Vector {
	int array[100];
	int size;
};

void VectorPushFront(struct Vector* vector, int val)
{
	assert(vector != NULL);
	if (size >= 100)
	{
		printf("顺序表满了！\n");
		return;
	}
	for (int i = 0; i < vector->size; i++)
	{
		vector[i + 1] = vector[i];
	}
	vector->array[0] = val;
	vector->size++;
}


//单项+无头+不循环 链表的尾删

typedef struct ListNode
{
	struct ListNode* next;
	int val;
}ListNode;

typedef struct List {
	ListNode* head;
}List;

ListNode* SListPopBack(struct List* list)
{
	if (list == NULL)
	{
		return NULL;
	}

	ListNode* cur = list->head;

	while (cur->next->next != NULL)
	{
		cur = cur->next;
	}
	free(cur->next);

	cur->next = NULL;

}

ListNode* SListNodeDelateval( List* list, int val)
{
	ListNode* cur = list->head;
	ListNode* prev = cur;

	while (cur->next != NULL)
	{

		if (cur->val == val)
		{
			prev->next = cur->next;
			free(cur);
			cur->val = 0;
			cur = NULL;
		}
		prev = cur;
		cur = cur->next;

	}
}


//冒泡排序

void Swap(int* a, int* b)
{
	int tmp = 0;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
void BubbleSort(int array[], int size)
{
	int i = 0;
	int j = 0;
	int isSort = 0;

	for (i = 0; i < size - 1; i++)
	{
		isSort = 0;
		for (j = 0; j < size - 1 - i; j++)
		{
			if (array[j] > array[j + 1])
			{
				Swap(array + j, array + j + 1);
				isSort = 1;
			}
		}

		if (isSort == 0)
		{
			break;
		}
	}
}

//复杂链表的复制

typedef struct RListNode {
	int val;
	RListNode* random;
	RListNode* next;
}	RListNode;


int Length(RListNode *head)
{
	int count = 0;
	for (RListNode *cur = head; cur != NULL; cur = cur->next;)
	{
		count++;
	}

	return count;
}

RListNode* RListCopy(RListNode* head)
{
	int length = Length(head);
	RListNode* cur = head;
	RListNode* Copy_cur = (RListNode*)malloc(sizeof(RListNode)*length);//有问题
	RListNode* Copy_head = Copy_cur;
	RListNode* next = cur->next;
	RListNode* Copy_next = Copy_cur->next;

	while (cur->next != NULL)
	{
		Copy_cur->val = cur->val;

		cur = cur->next;
		
		Copy_cur = Copy_cur->next;
	}
	Copy_cur->next = NULL;

	while (cur != NULL)
	{
		next = cur->next;
		Copy_next = Copy_cur->next;

		cur->next = Copy_cur;
		Copy_cur->next = cur->next;

		cur = next;
		Copy_cur = Copy_next;

	}

	cur = head;
	Copy_cur = Copy_head;

	while(cur != NULL)
	{
		Copy_cur->random = cur->random->next;

		cur = cur - next;
		Copy_cur = Copy_cur->next;

	}

	cur = head;
	Copy_cur = Copy_head;

	while (cur != NULL)
	{
		cur->next = Copy_cur->next;
		Copy_cur->next = cur->next->next;

		cur = cur->next;
		if (cur->next != NULL) 
		{
			Copy_cur = Copy_cur->next;
		}
	}

	Copy_cur->next = NULL;

	return Copy_head;

}