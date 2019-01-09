#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1  
#define OVERFLOW -2
#define STACK_INIT_SIZE 100   //�洢�ռ��ʼ������
#define STACKINCREMENT 10   //�洢�ռ��������

typedef char SElemType;
typedef char OperandType;   //���ʽ��ֵ����������
typedef int Status;

typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;


//����һ����ջ
Status InitStack(SqStack *S)
{
	S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S->base)
	{
		printf("�ڴ����ʧ��!\n");
		exit(OVERFLOW);
	}

	S->top = S->base;
	S->stacksize = STACKINCREMENT;
	return OK;
}

//��ջ��Ϊ�գ�����e����S��ջ��Ԫ�أ�������OK�����򷵻�ERROR
Status GetTop(SqStack *S, SElemType *e)
{
	if (S->top == S->base)
		return ERROR;

	*e = *(S->top - 1);
	return OK;
}

//����Ԫ��eΪ�µ�ջ��Ԫ��
Status Push(SqStack *S, SElemType e)
{
	if (S->top - S->base >= STACK_INIT_SIZE)   //ջ���� ׷�Ӵ洢�ռ�
	{
		S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S->base)
		{
			printf("�ڴ����ʧ��!\n");
			exit(OVERFLOW);
		}

		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT;
	}

	*S->top++ = e;

	return OK;
}

//��ջ��Ϊ�գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������Ok�����򷵻�ERROR
Status Pop(SqStack *S, SElemType *e)
{
	if (S->top == S->base)
		return ERROR;

	*e = *--S->top;

	return OK;
}
//����ջS��ʹ�䲻������
Status StackDestroy(SqStack *S)
{
	free(S->base);
	S->base = NULL;
	S->top = NULL;
	S->stacksize = 0;
	return OK;
}

//���ջS������ջ��ָ��
void ClearStack(SqStack *S)
{
	S->top = S->base;
}

//���ݽ̿����3.1���ж������ŵ����ȹ�ϵ
char Precede(char t1, char t2) 
{
	int i, j;
	char pre[][7] = {
		//�����֮������ȼ�������һ�ű��  
			{'>','>','<','<','<','>','>'},
			{'>','>','<','<','<','>','>'},
			{'>','>','>','>','<','>','>'},
			{'>','>','>','>','<','>','>'},
			{'<','<','<','<','<','=','0'},
			{'>','>','>','>','0','>','>'},
			{'<','<','<','<','<','0','='} };
	switch (t1) {
	case '+': i = 0; break;
	case '-': i = 1; break;
	case '*': i = 2; break;
	case '/': i = 3; break;
	case '(': i = 4; break;
	case ')': i = 5; break;
	case '=': i = 6; break;
	}
	switch (t2) {
	case '+': j = 0; break;
	case '-': j = 1; break;
	case '*': j = 2; break;
	case '/': j = 3; break;
	case '(': j = 4; break;
	case ')': j = 5; break;
	case '=': j = 6; break;
	}
	return pre[i][j];
}
//�ж�c�Ƿ�Ϊ�����
Status In(OperandType c)
{
	switch (c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
	case '=':
		return TRUE;
	default:
		return FALSE;
	}

}

//��Ԫ����(a theta b)
OperandType Operate(OperandType a, OperandType theta, OperandType b)
{
	OperandType c;
	switch (theta)
	{
	case '+':
		c = a + b;
		break;
	case '-':
		c = a - b;
		break;
	case '*':
		c = a * b;
		break;
	case '/':
		c = a / b;
		break;
	}
	return c;
}

//�������ʽ��ֵ����������㷨����OPTR��OPND�ֱ�Ϊ�����ջ��������ջ��OPΪ���������
OperandType EvaluateExpression()
{
	SqStack OPTR, OPND;
	OperandType a, b, d, x, theta;
	char c;   //����м���������ַ���
	char z[6];   //��������ַ���
	int i;
	InitStack(&OPTR);   //��ʼ�������ջ
	Push(&OPTR, '=');   //=�Ǳ��ʽ������
	InitStack(&OPND);   //��ʼ��������ջ

	c = getchar();
	GetTop(&OPTR, &x);
	while (c != '=' || x != '=')
	{
		if (In(c))   //��7�������֮һ
		{
			switch (Precede(x, c))
			{
			case '<':   //��ǰ�Ѿ�ѹջһ���������x���Ⱥ�һ���������c����ʱ���ͽ�cѹջ
				Push(&OPTR, c);
				c = getchar();
				break;
			case '=':
				Pop(&OPTR, &x);   //�����Ų�������һ�ַ�
				c = getchar();
				break;
			case '>':
				Pop(&OPTR, &theta);   //��ջ����������ѹ��OPND��
				Pop(&OPND, &b);
				Pop(&OPND, &a);
				Push(&OPND, Operate(a, theta, b));
				break;
			}
		}
		else if (c >= '0' && c <= '9')   //c�ǲ�����
		{
			i = 0;
			do
			{
				z[i] = c;
				i++;
				c = getchar();
			} while (c >= '0' && c <= '9');
			z[i] = 0;
			d = atoi(z);   //���ַ�����תΪ���ʹ���d
			Push(&OPND, d);
		}
		else   //cΪ�Ƿ��ַ�
		{
			printf("ERROR3\n");
			exit(1);
		}
		GetTop(&OPTR, &x);
	}
	GetTop(&OPND, &x);
	StackDestroy(&OPTR);
	StackDestroy(&OPND);
	return x;
}

int main()
{
	printf("�������������ʽ������Ҫ�ã�0-������������#����:\n");
	printf("%d\n", EvaluateExpression());
	system("pause");
	return 0;
}
