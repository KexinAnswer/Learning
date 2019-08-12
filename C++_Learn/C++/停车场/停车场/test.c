#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include <conio.h>

#define MAX 2 /*车库容量*/

#define price 3 /*每车每时刻费用*/

typedef struct node

{
	int num;

	int reachtime;

	int leavetime;

}CarNode; /*车辆信息结点*/

typedef struct NODE

{
	CarNode *stack[MAX + 1];

	int top;

}SeqStackCar; /*模拟车站*/

typedef struct car

{
	CarNode *data;

	struct car *next;

}QueueNode;

typedef struct Node

{
	QueueNode *head;

	QueueNode *rear;

}LinkQueueCar; /*模拟通道*/

/*---------------------------------------------------------------------------*/   /*函数声明部分*/

void InitStack(SeqStackCar *); /*初始化栈*/

int InitQueue(LinkQueueCar *); /*初始化便道*/

int Arrival(SeqStackCar *, LinkQueueCar *); /*车辆到达*/

void Leave(SeqStackCar *, SeqStackCar *, LinkQueueCar *); /*车辆离开*/

void List(SeqStackCar, LinkQueueCar); /*显示存车信息*/

void PRINT(CarNode *p);



/*---------------------------------------------------------------------------*/ 
void option()
{
	int i = 0;;

	char choice;

	printf("停车场管理系统");

	printf("\n********************************************************************************\n");

	printf("\t1.车辆到达--1 2.车辆离开--2  3.车辆信息--3  4.退出程序--4");

	printf("\n********************************************************************************\n");

	printf("\n\n\n\t                       是否进入该系统（y/n）？ ");

	choice = getchar();

	if (choice == 'N' || choice == 'n')
		exit(0);
	else
		printf("登陆成功!");

}


void InitStack(SeqStackCar *s) /*初始化栈*/

{
	int i;

	s->top = 0;

	for (i = 0; i <= MAX; i++)

		s->stack[s->top] = NULL;

}

int InitQueue(LinkQueueCar *Q) /*初始化便道*/

{
	Q->head = (QueueNode *)malloc(sizeof(QueueNode));

	if (Q->head != NULL)

	{
		Q->head->next = NULL;

		Q->rear = Q->head;

		return(1);

	}

	else

		return(-1);

}

void PRINT(CarNode *p) /*打印出站车的信息*/

{
	int A1, A2;

	printf("\n\t\t\t请输入离开时间:  ");

	scanf("%d", &(p->leavetime));

	printf("\n\t\t\t离开车辆的车牌号:  %d", p->num);

	printf("\n\n\t\t\t离开车辆到达时间:  %d ", p->reachtime);

	printf("\n\n\t\t\t离开车辆离开时间:  %d", p->leavetime);

	A1 = p->reachtime;

	A2 = p->leavetime;

	printf("\n\n\t\t\t停车场管理费用: %d", (A2 - A1)*price);

	free(p);

}

int Arrival(SeqStackCar *Enter, LinkQueueCar *W) /*车辆到达*/

{
	CarNode *p;

	QueueNode *t;

	p = (CarNode *)malloc(sizeof(CarNode));

	printf("\t\t\t请输入到达车辆车牌号:  ");

	scanf("%d", &(p->num));

	if (Enter->top < MAX) /*车场未满，车进车场*/

	{
		Enter->top++;

		printf("\n\t\t\t该车辆在停车场的位置是:  %d\n", Enter->top);

		printf("\n\t\t\t请输入该车辆到达的时间:  ");

		scanf("%d", &(p->reachtime));

		Enter->stack[Enter->top] = p;

		return(1);

	}

	else                    /*车场已满，车进便道*/

	{
		printf("\n\t\t\t停车场已满 该车辆需在便道上等待！");

		getchar();

		t = (QueueNode *)malloc(sizeof(QueueNode));

		t->data = p;

		t->next = NULL;

		W->rear->next = t;

		W->rear = t;

		return(1);

	}

}

void Leave(SeqStackCar *Enter, SeqStackCar *Temp, LinkQueueCar *W)  /*车辆离开*/

{
	int i=0;
	int room;

	CarNode *p, *t;

	QueueNode *q;

	/*判断车场内是否有车*/

	if (Enter->top > 0) /*有车*/

	{
		while (1) /*输入离开车辆的信息*/

		{
			printf("\t\t\t停车场里停放的车辆总数:  %d", Enter->top);

			printf("\n\n\t\t\t请输入要离开车辆的位置:  ");

			scanf("%d", &room);

			if (room >= 1 && room <= Enter->top)

				break;

		}

		while (Enter->top > room) /*车辆离开*/

		{
			Temp->top++;

			Temp->stack[Temp->top] = Enter->stack[Enter->top];

			Enter->stack[Enter->top] = NULL;

			Enter->top--;

		}

		p = Enter->stack[Enter->top];

		Enter->stack[Enter->top] = NULL;

		Enter->top--;

		while (Temp->top >= 1)

		{
			Enter->top++;

			Enter->stack[Enter->top] = Temp->stack[Temp->top];

			Temp->stack[Temp->top] = NULL;

			Temp->top--;

		}

		PRINT(p);

		/*判断通道上是否有车及车站是否已满*/

		if ((W->head != W->rear) && Enter->top < MAX) /*便道的车辆进入车场*/

		{
			q = W->head->next;

			t = q->data;

			Enter->top++;

			printf("\n\n\t\t\t便道的%d号车进入车场第%d位置.", t->num, Enter->top);

			printf("\n\n\t\t\t请输入现在的时间:");

			scanf("%d", &(t->reachtime));

			W->head->next = q->next;

			if (q == W->rear)

				W->rear = W->head;

			Enter->stack[Enter->top] = t;

			free(q);

		}

		else

			printf("\n\n\t\t\t便道里没有车.\n");

	}

	else

		printf("\n\n\t\t\t车场里没有车."); /*没车*/

}

void List1(SeqStackCar *S) /*列表显示车场信息*/

{
	int i;

	if (S->top > 0) /*判断车站内是否有车*/

	{
		printf("\n\t\t\t车场:");

		printf("\n\n\t\t\t位置  到达时间  车牌号\n");

		for (i = 1; i <= S->top; i++)

		{
			printf("%26d", i);

			printf("%6d", S->stack[i]->reachtime);

			printf("%10d", S->stack[i]->num);

			printf("\n");

		}

	}

	else

		printf("\n\t\t\t车场里没有车");

}

void List2(LinkQueueCar *W) /*列表显示便道信息*/

{
	QueueNode *p;

	p = W->head->next;

	if (W->head != W->rear) /*判断通道上是否有车*/

	{
		printf("\n\t\t\t等待车辆的号码为:  ");

		while (p != NULL)

		{
			printf("%-10d", p->data->num);

			p = p->next;

		}

		printf("\n");

	}

	else

		printf("\n\t\t\t便道里没有车.");

}

void List(SeqStackCar S, LinkQueueCar W)

{
	int flag, tag;

	flag = 1;

	while (flag)

	{
		printf("\n\t\t\t请选择 1|2|3:");

		printf("\n\n\t\t\t1.车场\n\n\t\t\t2.便道\n\n\t\t\t3.返回\n\n\t\t\t");

		while (1)

		{
			scanf("%d", &tag);

			if (tag >= 1 || tag <= 3) break;

			else printf("\n\t\t\t请选择 1|2|3:");

		}

		switch (tag)

		{
		case 1:List1(&S); break; /*列表显示车场信息*/

		case 2:List2(&W); break; /*列表显示便道信息*/

		case 3:flag = 0; break;

		default: break;

		}

	}

}


int main()
{
	SeqStackCar Enter, Temp;

	LinkQueueCar Wait;

	int ch;

	system("graftabl 936");

	option();

	InitStack(&Enter); /*初始化车站*/

	InitStack(&Temp); /*初始化让路的临时栈*/

	InitQueue(&Wait); /*初始化通道*/

	while (1)

	{
		//clrscr();

		system("cls");

		printf("\n\n\t\t\t1. 车辆到达 请选择 1");

		printf("\n\n\t\t\t2. 车辆离开 请选择 2");

		printf("\n\n\t\t\t3. 车辆信息 请选择 3");

		printf("\n\n\t\t\t4. 退出程序 请选择 4");

		printf("\n\n\t\t\t现在请选择以上信息 :  ");

		while (1)

		{
			scanf("%d", &ch);

			printf("\n");

			if (ch >= 1 && ch <= 4)break;

			else

				printf("\n\t\t\t错误！请再次做出选择！\n\n\t\t\t");

		}

		switch (ch)

		{
		case 1:Arrival(&Enter, &Wait); break; /*车辆到达*/

		case 2:Leave(&Enter, &Temp, &Wait); break; /*车辆离开*/

		case 3:List(Enter, Wait); break; /*列表打印信息*/

		case 4:exit(0); /*退出主程序*/

		default:  break;
		}

	}

	system("pause");
	return 0;

}

/*------------------------------------------------------------------------------*/
