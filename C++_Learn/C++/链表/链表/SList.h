#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


//��ͷ+����+��ѭ������
typedef int SLDataType;

//��������ڵ�
typedef struct SLNode
{
	SLDataType val;
	struct SLNode *next;
}	SListNode;


//����һ������
typedef struct SList
{
	SListNode *first;
}	SList;

SListNode* BuySListNode(SLDataType x)
{
	SListNode *node = (SListNode*)malloc(sizeof(SListNode));
	node->val = x;
	node->next = NULL;
	return node;
}
//����ĳ�ʼ��
void SListInit(SList *list)
{
	assert(list != NULL);
	list->first = NULL;
}

//��������
void SListDestroy(SList *list)
{
	assert(list != NULL);

	SListNode *cur = list->first;
	SListNode *next = NULL;

	while (cur != NULL)
	{
		next = cur->next;
		free(cur);
		cur = NULL;
		cur = cur->next;
	}

}

//ͷ��
void SListPushFront(SList *list, SLDataType x)
{
	assert(list != NULL);

	SListNode *first = BuySListNode(x);
	assert(first != NULL);

	first->val = x;
	first->next = list->first;
	list->first = first;
}


//ͷɾ
void SListPopFront(SList *list)
{
	assert(list != NULL);

	SListNode *cur = list->first->next;

	free(list->first);
	list->first = NULL;

	list->first = cur;
}


//β��
void SListPustBack(SList *list, SLDataType x)
{
	assert(list != NULL);

	SListNode *cur = list->first;
	SListNode *node = BuySListNode(x);
	
	while (cur->next != NULL)
	{
		cur = cur->next;
	}

	cur->next = node;
	node->val = x;
	node->next = NULL;

}

//βɾ
void SListPopBack(SList *list)
{
	assert(list != NULL);

	SListNode *cur = list->first;

	while (cur->next->next != NULL)
	{
		cur = cur->next;
	}

	free(cur->next);
	cur->next = NULL;

}

//����value ���ؽڵ��ַ
SListNode * SListFind(SList *list, SLDataType x)
{
	assert(list != NULL);
	assert(list->first->next != NULL);
	
	SListNode *cur = list->first;

	while (cur != NULL)
	{
		if (cur->val == x)
		{
			return cur;
		}
		cur = cur->next;
	}

	return NULL;
}

//�� pos ǰ����һ���ڵ�
void SListInsertBefore(SList *list, SListNode *pos, SLDataType value)
{
	assert(list != NULL);
	assert(pos != NULL);

	SListNode *cur = list->first;

	while (cur->next != pos && cur != NULL)
	{
		cur = cur->next;
	}
	
	SListNode *node = BuySListNode(value);

	node->val = value;
	
	node->next = cur->next;
	cur-> next = node;

}


//ɾ��pos�����һ���ڵ�
void SListEraseAfter(SList *list, SListNode *pos)
{
	assert(list != NULL);
	assert(list->first->next != NULL);

	SListNode *cur = list->first;
	SListNode *next = NULL;

	while (cur != pos && cur != NULL)
	{
		cur = cur->next;
	}

	next = cur->next;

	cur-> next = cur->next->next;
	
	free(next);
	next = NULL;

}
//
//void SListRemove(SList *list, SLDataType x)
//{
//
//}