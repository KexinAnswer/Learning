#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int* p = calloc(10, sizeof(int));

	int* ptr = NULL;

	//int* p = (int*)malloc(10*sizeof(int));



	if (p == NULL)

	{

		printf("%s\n", strerror(errno));

	}

	else

	{

		int i = 0;

		for (i = 0; i<10; i++)

		{

			printf("%d\n", p[i]);

		}

	}

	//动态内存的调整

	ptr = realloc(p, 11 * sizeof(int));

	if (ptr != NULL)

	{

		p = ptr;

	}

	free(p);

	p = NULL;

	system("pause");

	return 0;
}