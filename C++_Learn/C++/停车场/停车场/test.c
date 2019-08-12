#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include <conio.h>

#define MAX 2 /*��������*/

#define price 3 /*ÿ��ÿʱ�̷���*/

typedef struct node

{
	int num;

	int reachtime;

	int leavetime;

}CarNode; /*������Ϣ���*/

typedef struct NODE

{
	CarNode *stack[MAX + 1];

	int top;

}SeqStackCar; /*ģ�⳵վ*/

typedef struct car

{
	CarNode *data;

	struct car *next;

}QueueNode;

typedef struct Node

{
	QueueNode *head;

	QueueNode *rear;

}LinkQueueCar; /*ģ��ͨ��*/

/*---------------------------------------------------------------------------*/   /*������������*/

void InitStack(SeqStackCar *); /*��ʼ��ջ*/

int InitQueue(LinkQueueCar *); /*��ʼ�����*/

int Arrival(SeqStackCar *, LinkQueueCar *); /*��������*/

void Leave(SeqStackCar *, SeqStackCar *, LinkQueueCar *); /*�����뿪*/

void List(SeqStackCar, LinkQueueCar); /*��ʾ�泵��Ϣ*/

void PRINT(CarNode *p);



/*---------------------------------------------------------------------------*/ 
void option()
{
	int i = 0;;

	char choice;

	printf("ͣ��������ϵͳ");

	printf("\n********************************************************************************\n");

	printf("\t1.��������--1 2.�����뿪--2  3.������Ϣ--3  4.�˳�����--4");

	printf("\n********************************************************************************\n");

	printf("\n\n\n\t                       �Ƿ�����ϵͳ��y/n���� ");

	choice = getchar();

	if (choice == 'N' || choice == 'n')
		exit(0);
	else
		printf("��½�ɹ�!");

}


void InitStack(SeqStackCar *s) /*��ʼ��ջ*/

{
	int i;

	s->top = 0;

	for (i = 0; i <= MAX; i++)

		s->stack[s->top] = NULL;

}

int InitQueue(LinkQueueCar *Q) /*��ʼ�����*/

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

void PRINT(CarNode *p) /*��ӡ��վ������Ϣ*/

{
	int A1, A2;

	printf("\n\t\t\t�������뿪ʱ��:  ");

	scanf("%d", &(p->leavetime));

	printf("\n\t\t\t�뿪�����ĳ��ƺ�:  %d", p->num);

	printf("\n\n\t\t\t�뿪��������ʱ��:  %d ", p->reachtime);

	printf("\n\n\t\t\t�뿪�����뿪ʱ��:  %d", p->leavetime);

	A1 = p->reachtime;

	A2 = p->leavetime;

	printf("\n\n\t\t\tͣ�����������: %d", (A2 - A1)*price);

	free(p);

}

int Arrival(SeqStackCar *Enter, LinkQueueCar *W) /*��������*/

{
	CarNode *p;

	QueueNode *t;

	p = (CarNode *)malloc(sizeof(CarNode));

	printf("\t\t\t�����뵽�ﳵ�����ƺ�:  ");

	scanf("%d", &(p->num));

	if (Enter->top < MAX) /*����δ������������*/

	{
		Enter->top++;

		printf("\n\t\t\t�ó�����ͣ������λ����:  %d\n", Enter->top);

		printf("\n\t\t\t������ó��������ʱ��:  ");

		scanf("%d", &(p->reachtime));

		Enter->stack[Enter->top] = p;

		return(1);

	}

	else                    /*�����������������*/

	{
		printf("\n\t\t\tͣ�������� �ó������ڱ���ϵȴ���");

		getchar();

		t = (QueueNode *)malloc(sizeof(QueueNode));

		t->data = p;

		t->next = NULL;

		W->rear->next = t;

		W->rear = t;

		return(1);

	}

}

void Leave(SeqStackCar *Enter, SeqStackCar *Temp, LinkQueueCar *W)  /*�����뿪*/

{
	int i=0;
	int room;

	CarNode *p, *t;

	QueueNode *q;

	/*�жϳ������Ƿ��г�*/

	if (Enter->top > 0) /*�г�*/

	{
		while (1) /*�����뿪��������Ϣ*/

		{
			printf("\t\t\tͣ������ͣ�ŵĳ�������:  %d", Enter->top);

			printf("\n\n\t\t\t������Ҫ�뿪������λ��:  ");

			scanf("%d", &room);

			if (room >= 1 && room <= Enter->top)

				break;

		}

		while (Enter->top > room) /*�����뿪*/

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

		/*�ж�ͨ�����Ƿ��г�����վ�Ƿ�����*/

		if ((W->head != W->rear) && Enter->top < MAX) /*����ĳ������복��*/

		{
			q = W->head->next;

			t = q->data;

			Enter->top++;

			printf("\n\n\t\t\t�����%d�ų����복����%dλ��.", t->num, Enter->top);

			printf("\n\n\t\t\t���������ڵ�ʱ��:");

			scanf("%d", &(t->reachtime));

			W->head->next = q->next;

			if (q == W->rear)

				W->rear = W->head;

			Enter->stack[Enter->top] = t;

			free(q);

		}

		else

			printf("\n\n\t\t\t�����û�г�.\n");

	}

	else

		printf("\n\n\t\t\t������û�г�."); /*û��*/

}

void List1(SeqStackCar *S) /*�б���ʾ������Ϣ*/

{
	int i;

	if (S->top > 0) /*�жϳ�վ���Ƿ��г�*/

	{
		printf("\n\t\t\t����:");

		printf("\n\n\t\t\tλ��  ����ʱ��  ���ƺ�\n");

		for (i = 1; i <= S->top; i++)

		{
			printf("%26d", i);

			printf("%6d", S->stack[i]->reachtime);

			printf("%10d", S->stack[i]->num);

			printf("\n");

		}

	}

	else

		printf("\n\t\t\t������û�г�");

}

void List2(LinkQueueCar *W) /*�б���ʾ�����Ϣ*/

{
	QueueNode *p;

	p = W->head->next;

	if (W->head != W->rear) /*�ж�ͨ�����Ƿ��г�*/

	{
		printf("\n\t\t\t�ȴ������ĺ���Ϊ:  ");

		while (p != NULL)

		{
			printf("%-10d", p->data->num);

			p = p->next;

		}

		printf("\n");

	}

	else

		printf("\n\t\t\t�����û�г�.");

}

void List(SeqStackCar S, LinkQueueCar W)

{
	int flag, tag;

	flag = 1;

	while (flag)

	{
		printf("\n\t\t\t��ѡ�� 1|2|3:");

		printf("\n\n\t\t\t1.����\n\n\t\t\t2.���\n\n\t\t\t3.����\n\n\t\t\t");

		while (1)

		{
			scanf("%d", &tag);

			if (tag >= 1 || tag <= 3) break;

			else printf("\n\t\t\t��ѡ�� 1|2|3:");

		}

		switch (tag)

		{
		case 1:List1(&S); break; /*�б���ʾ������Ϣ*/

		case 2:List2(&W); break; /*�б���ʾ�����Ϣ*/

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

	InitStack(&Enter); /*��ʼ����վ*/

	InitStack(&Temp); /*��ʼ����·����ʱջ*/

	InitQueue(&Wait); /*��ʼ��ͨ��*/

	while (1)

	{
		//clrscr();

		system("cls");

		printf("\n\n\t\t\t1. �������� ��ѡ�� 1");

		printf("\n\n\t\t\t2. �����뿪 ��ѡ�� 2");

		printf("\n\n\t\t\t3. ������Ϣ ��ѡ�� 3");

		printf("\n\n\t\t\t4. �˳����� ��ѡ�� 4");

		printf("\n\n\t\t\t������ѡ��������Ϣ :  ");

		while (1)

		{
			scanf("%d", &ch);

			printf("\n");

			if (ch >= 1 && ch <= 4)break;

			else

				printf("\n\t\t\t�������ٴ�����ѡ��\n\n\t\t\t");

		}

		switch (ch)

		{
		case 1:Arrival(&Enter, &Wait); break; /*��������*/

		case 2:Leave(&Enter, &Temp, &Wait); break; /*�����뿪*/

		case 3:List(Enter, Wait); break; /*�б��ӡ��Ϣ*/

		case 4:exit(0); /*�˳�������*/

		default:  break;
		}

	}

	system("pause");
	return 0;

}

/*------------------------------------------------------------------------------*/
