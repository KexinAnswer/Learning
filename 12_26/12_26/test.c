#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
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
	system("pause");
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
			printf("合法！\n");
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
	if (s[j] >= '0'&&s[j] <= '9')
		++j;
	else
	{
		printf("不合法！\n");
		k = 1;
	}
}

