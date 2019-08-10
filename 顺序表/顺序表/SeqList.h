#pragma once


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


typedef int SLDatatype;

typedef struct SeqList
{
	SLDatatype *array;
	int size;
	int capicity;

}	SeqList;

void SeqListInit(SeqList  *list, int capicity)
{
	assert(list != NULL);

	SLDatatype *Memory = (SLDatatype*)malloc(sizeof(SeqList) * capicity);

	assert(Memory != NULL);

	list->array = Memory;
	list->capicity = capicity;
	list->size = 0;
}

void SeqListDestroy(SeqList *list)
{
	list->capicity = 0;
	list->size = 0;
	free(list->array);
	list = NULL;
	
}

void CheckCapicity(SeqList *list)
{
	assert(list != NULL);

	if (list->size < list->capicity)
	{
		return;
	}
	list->capicity = 2 * list->capicity;
	SLDatatype *Memory = (SLDatatype*)malloc(sizeof(SeqList) * list->capicity);

	assert(Memory != NULL);

	list->array = Memory;
} 

void SeqListPushBack(SeqList *list, SLDatatype x)
{
	CheckCapicity(list);
	list->array[list->size] = x;

	list->size++;

}

void SeqListPopBack(SeqList *list)
{
	list->size--;

}

void SeqListPushFront(SeqList *list, SLDatatype x)
{
	assert(list != NULL);
	
	CheckCapicity(list);
	list->size++;

	for (int i = list->size; i > 0; i--)
	{
		list->array[i] = list->array[i - 1];
	}

	list->array[0] = x;
}

void SeqListPopFront(SeqList *list)
{
	for (int i = 0; i < list->size; i++)
	{
		list->array[i] = list->array[i + 1];
	}

	list->size--;
}

int SeqListFind(SeqList *list, SLDatatype x)
{
	for (int i = 0; i < list->size; i++)
	{
		if (list->array[i] == x)
		{
			return i;
		}
	}

	return -1;
}

void SeqListInsert(SeqList *list, int pos, SLDatatype x)
{
	assert(list != NULL);
	list->size++;

	CheckCapicity(list);

	for (int i = list->size; i > pos; i--)
	{
		list->array[i] = list->array[i-1];
	}

	list->array[pos] = x;
}

void SeqListErase(SeqList *list, int pos)
{
	assert(list != NULL);

	for (int i = pos; i < list->size - 1; i++)
	{
		list->array[i] = list->array[i + 1];
	}

	list->size--;
}

void SeqListRemove(SeqList *list, SLDatatype x)
{
	assert(list != NULL);

	int pos = SeqListFind(list, x);

	if (pos != -1)
	{
		SeqListErase(list, pos);
	}
}

void SeqListModify(SeqList *list, int pos, SLDatatype x)
{
	assert(pos > 0 && pos < list->size);

	list->array[pos] = x;

}

void SeqListPrint(SeqList *list)
{
	for (int i = 0; i < list->size; i++)
	{
		printf("%d ", list->array[i]);
	}

	printf("\n");
}

int SeqListEmpty(SeqList *list)
{
	return list->size == 0;
}

int SeqListSize(const SeqList *list)
{
	return list->size; 
}