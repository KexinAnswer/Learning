#define _CRT_SECURE_NO_WARNINGS 1


#include <stdio.h>
#include <stdlib.h>
int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 5 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	int ret = 0;
	for (int i = 0; i < sz; i++)
	{
		ret = arr[i] ^ ret;
	}

	ret = ret ^ 0;
	printf("%d\n",ret);
	
	system("pause");
	return 0;
}