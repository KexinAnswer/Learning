#define _CRT_SECURE_NO_WARNINGS 1

//中间代码生成器
//#include<string.h>
//#include<ctype.h>
//#include<stdio.h>
//#include<math.h>
//char a[20], optr[10], s, op;
//int i, j, k, opond[10], x1, x2, x3;
//int operand(s)
//{
//	if((s >= 48) && (s <= 57))   
//		return 1;
//	else  
//		return 0;
//}
//int f(s)
//{
//	switch (s)
//	{
//		case'+ ':
//			return(4);
//		case'-':
//			return(4);
//		case'*':
//			return(6);
//		case'/':
//			return(4);
//		case'(':
//			return(2);
//		case')':
//			return(6);
//		case'#':
//			return(0);
//		default:
//			printf("error!\n");
//	}
//
//	return -1;
//}
//int g(s)
//{
//	switch(s)
//	{
//		case'+':
//			return(3);
//		case'-':
//			return(3);
//		case'*':
//			return(5);
//		case'/':
//			return(5);
//		case'(':
//			return(7);
//		case')':
//			return(2);
//		case'#':
//			return(0);
//		default:
//			printf("error!\n");
//	}
//
//	return -1;
//}
//void get()
//{
//	s = a[i];
//	i = i + 1;
//}
//int main()
//{
//	printf("please input your exoression : \n");
//	i = 0;
//	do
//	{
//		i = i + 1;
//		scanf("%c", &a[i]);
//	} while (a[i] != '#');
//	i = 1;
//	j = k = 1;
//	optr[j] = '#';
//	get();
//	while (!((optr[j] == '#' && (s == '#'))))
//	{
//		if (operand(s))
//		{
//			opond[k] = s - 48;
//			k = k + 1;
//			get();
//		}
//		else if (f(optr[j]>g(s)))
//		{
//			op = optr[j];
//			j = j - 1;
//			x1 = opond[k - 1];
//			k = k - 1;
//
//			x2 = opond[k - 1];
//			k = k - 1;
//			switch(op)
//			{
//				case'+':
//					x3 = x1 + x2; break;
//				case'*':
//					x3 = x1*x2; break;
//				case'-':
//					x3 = x1 - x2; break;
//				case'/':
//					x3 = x1 / x2; break;
//			}
//			opond[k] = x3;
//			k++;
//			printf("%c, %d, %d, %d\n", op, x1, x2, x3);
//		}
//		else if (f(optr[j])<g(s))
//		{
//			j = j + 1;
//			optr[j] = s;
//			get();
//		}
//		else if (f(optr[j]) == g(s))
//		{
//			if (optr[j] == '(' || ')')
//			{
//				j = j - 1;
//				get();
//			}
//			else 
//				printf("error!!\n");
//		}
//		else 
//			printf("error!!!\n");
//	}
//}

//
//
///* Note:Your choice is C IDE */
//#include "stdio.h"
//#include <stdlib.h>
//#include "string.h"
//char a[20], optr[10], s, op;
//int i, j, k, opnd[10], x1, x2, x3;
//int operand(char s)
//{
//	if ((s >= 48) && (s <= 57))
//		return 1;
//	else
//		return 0;
//}
//int f(char s)
//{
//	switch (s){
//	case'+':return 6;
//	case'-':return 8;
//	case'*':return 10;
//	case'/':return 12;
//	case'(':return 2;
//	case')':return 12;
//	case'#':return 2;
//	default:printf("error");
//	}
//}
//int g(char s)
//{
//	switch (s){
//	case'+':return 5;
//	case'-':return 7;
//	case'*':return 9;
//	case'/':return 11;
//	case'(':return 13;
//	case')':return 2;
//	case'#':return 2;
//	default:printf("error");
//	}
//}
//void get()
//{
//	s = a[i];
//	i = i + 1;
//}
//
//
//int main()
//{
//	printf("请输入算数表达式，并以‘#’结束:\n");
//	i = 0;
//	do
//	{
//		scanf("%c", &a[i]);
//		i++;
//	} while (a[i - 1] != '#');
//	i = 0;
//	j = 0;
//	k = 0;
//	optr[j] = '#';
//	get();
//	while ((optr[j] != '#') || (s != '#'))
//	{
//		if (operand(s))
//		{
//			opnd[k] = s - 48;
//			k = k + 1;
//			get();
//		}
//		else if (f(optr[j])<g(s))
//		{
//			j = j + 1;
//			optr[j] = s;
//			get();
//		}
//		else if (f(optr[j]) == g(s))
//		{
//			j = j - 1;
//			get();
//		}
//		else if (f(optr[j])>g(s))
//		{
//			op = optr[j];
//			j = j - 1;
//			x2 = opnd[k - 1];
//			x1 = opnd[k - 2];
//			k = k - 2;
//			switch (op){
//			case'+':x3 = x1 + x2; break;
//			case'-':x3 = x1 - x2; break;
//			case'*':x3 = x1 * x2; break;
//			case'/':x3 = x1 / x2; break;
//			}
//			opnd[k] = x3;
//			k = k + 1;
//			printf("(%c,%d,%d,%d)\n", op, x1, x2, x3);
//		}
//	}
//	system("pause");
//	return 0;
//	
//}



/* Note:Your choice is C IDE */
//#include "stdio.h"
//#include "string.h"
//#include <stdlib.h>
//int i, j, k;
//char s;
//char a[20], token[20];
//int letter()
//{
//	if ((s >= 97) && (s <= 122))return 1;
//	else return 0;
//}
//int Digit()
//{
//	if ((s >= 48) && (s <= 57))return 1;
//	else return 0;
//}
//void get()
//{
//	s = a[i];
//	i = i + 1;
//}
//void retract()
//{
//	i = i - 1;
//}
//int lookup()
//{
//	if (strcmp(token, "while") == 0)
//		return 1;
//	else if (strcmp(token, "if") == 0)
//		return 2;
//	else if (strcmp(token, "else") == 0)
//		return 3;
//	else if (strcmp(token, "switch") == 0)
//		return 4;
//	else if (strcmp(token, "case") == 0)
//		return 5;
//	else return 0;
//}
//
//void main()
//{
//	printf("please input you source program,end('#'):\n");
//	i = 0;
//	do
//	{
//		i = i + 1;
//		scanf("%c", &a[i]);
//	} while (a[i] != '#');
//	i = 1;
//	memset(token, 0, sizeof(char)* 10);
//	j = 0;
//	get();
//	while (s != '#')
//	{
//		if (s == ' ' || s == 10 || s == 13)
//			get();
//		else
//		{
//			switch (s)
//			{
//			case'a':
//			case'b':
//			case'c':
//			case'd':
//			case'e':
//			case'f':
//			case'g':
//			case'h':
//			case'i':
//			case'j':
//			case'k':
//			case'l':
//			case'm':
//			case'n':
//			case'o':
//			case'p':
//			case'q':
//			case'r':
//			case's':
//			case't':
//			case'u':
//			case'v':
//			case'w':
//			case'x':
//			case'y':
//			case'z':
//				while (Digit() || letter())
//				{
//					token[j] = s;
//					j = j + 1;
//					get();
//				}
//				retract();
//				k = lookup();
//				if (k == 0)
//					printf("(6,%s)\n", token);
//				else
//					printf("(%d,null)\n", k);
//				break;
//			case'0':
//			case'1':
//			case'2':
//			case'3':
//			case'4':
//			case'5':
//			case'6':
//			case'7':
//			case'8':
//			case'9':
//				while (Digit())
//				{
//					token[j] = s;
//					j = j + 1;
//					get();
//				}
//				retract();
//				printf("(%d,%s)\n", 7, token);
//				break;
//			case'+':
//				printf("(+,null)\n");
//				break;
//			case'-':
//				printf("(-,null)\n");
//				break;
//			case'*':
//				printf("(*,null)\n");
//				break;
//			case'<':
//				get();
//				if (s == '=')
//					printf("(relop,LE)\n");
//				else
//				{
//					retract();
//					printf("(relop,LT)\n");
//				}
//				break;
//			case'=':
//				get();
//				if (s == '=')
//					printf("(relop,EQ)\n");
//				else
//				{
//					retract();
//					printf("(=,null)\n");
//				}
//				break;
//			case';':
//				printf("(;,null)\n");
//				break;
//			default:
//				printf("(%c,error)\n", s);
//				break;
//			}
//			memset(token, 0, sizeof(char)* 10);
//			j = 0;
//			get();
//		}
//	}
//	system("pause");
//	return 0;
//}

#include <stdio.h>
#include <stdlib.h>
void E();
void T();
void E1();
void T1();
void F();
void i();


char s[100];
int j, k;

int main(){
	printf("请输入一个语句，以#号结束语句\n");
	while (1){
		k = 0;
		j = 0;

		scanf("%s", &s);

		if (s[0] == '#')
			return 0;

		E();

		if (k == 0){
			if (s[j] == '#')
				printf("合法！\n");
		}

		printf("请输入一个语句，以#号结束语句\n");

	}
	return 1;
}

void E()
{
	if (k == 0)
	{
		T();
		E1();
	}
}

void E1()
{
	if (k == 0)
	{
		if (s[j] == '+')
		{
			++j;
			T();
			E1();
		}
		else if (s[j] != '#'&&s[j] != ')')
		{
			printf("不合法！\n");
			k = 1;
		}
	}
}

void T()
{
	if (k == 0)
	{
		F();
		T1();
	}
}

void T1()
{
	if (k == 0)
	{
		if (s[j] == '*')
		{
			++j;
			F();
			T1();
		}
		else if (s[j] != '#'&&s[j] != ')'&&s[j] != '+')
		{
			printf("不合法！\n");
			k = 1;
		}
	}
}

void F()
{
	if (k == 0)
	{
		if (s[j] == '(')
		{
			++j;
			E();
			if (s[j] == ')')
				++j;
			else if (s[j] == '#')
			{
				printf("不合法！\n括号不匹配\n");
				++j;
				k = 1;
			}
		}
		else  i();
	}
}

void i(){
	if (s[j] >= '0'&& s[j] <= '9')
		++j;
	else
	{
		printf("不合法！\n");
		k = 1;
	}
	system("pause");
	return 0;
}
