#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
//
//void change1(int a, int b)
//{
//	a = 5;
//	b = 10;
//}
//
//void change2(int* a, int* b)
//{
//	*a = 5;
//	*b = 10;
//}
//
//int main()
//{
//	int a = 2;
//	int b = 3;
//	
//	printf("a = %d b = %d\n", a, b);
//	
//	change1(a, b);
//	printf("a = %d b = %d\n", a, b);
//
//	change2(&a,&b);
//	printf("a = %d b = %d\n", a, b);
//
//
//	system("pause");
//	return 0;
//}
void test(char** p)
{

}
int main()
{
	char c = 'w';
	char *pc = &c;
	char** ppc = &pc;
	char* arr[10] = {0};
	test(&pc);
	test(ppc);
	test(arr);


	system("pause");
	return 0;

}