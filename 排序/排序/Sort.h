#pragma once

#include <stdio.h>

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void BubbleSort(int arr[], int size)
{
	int isSort = 0;
	for (int i = 0; i < size - 1; ++i)
	{
		isSort = 0;
		for (int j = 0; j < size - i -1 ; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr+j, arr+j + 1);
				isSort = 1;
			}
		}

		if (isSort == 0)
			break;
	}
}


void InsertSort(int arr[], int size)
{
	int i, j;
	for (i = 1; i < size; i++)
	{
		int k = arr[i];
		for (j = i - 1; j >= 0; j--)
		{

			if (arr[i] < arr[j + 1])
			{
				break;
			}
			else
			{
				arr[j + 1] = arr[j];
			}

		}

		arr[j + 1] = k;

	}


}

void Print(int arr[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");
}

void Test()
{
	int arr[] = { 9 , 8 ,7 ,6,5,4,3,2,1 };
	int size = sizeof(arr) / sizeof(arr[0]);

	//BubbleSort(arr, size);

	InsertSort(arr, size);
	Print(arr, size);
}

