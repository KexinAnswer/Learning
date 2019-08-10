#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


//无头+单项+非循环链表
typedef int SLDataType;

//定义链表节点
typedef struct SLNode
{
	SLDataType val;
	struct SLNode *next;
}	SListNode;


//定义一个链表
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
//链表的初始化
void SListInit(SList *list)
{
	assert(list != NULL);
	list->first = NULL;
}

//销毁链表
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

//头插
void SListPushFront(SList *list, SLDataType x)
{
	assert(list != NULL);

	SListNode *first = BuySListNode(x);
	assert(first != NULL);

	first->val = x;
	first->next = list->first;
	list->first = first;
}


//头删
void SListPopFront(SList *list)
{
	assert(list != NULL);

	SListNode *cur = list->first->next;

	free(list->first);
	list->first = NULL;

	list->first = cur;
}


//尾插
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

//尾删
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

//查找value 返回节点地址
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

//在 pos 前插入一个节点
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


//删除pos后面的一个节点
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