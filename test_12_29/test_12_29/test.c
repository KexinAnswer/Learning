#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

//����һ���������� nums ��һ��Ŀ��ֵ target�������ڸ��������ҳ���ΪĿ��ֵ���� ���� ���������������ǵ������±ꡣ
//����Լ���ÿ������ֻ���Ӧһ���𰸡����ǣ��㲻���ظ��������������ͬ����Ԫ�ء�
//ʾ�� :
//���� nums = [2, 7, 11, 15], target = 9
//
//��Ϊ nums[0] + nums[1] = 2 + 7 = 9
//���Է���[0, 1]
///**
//* Note: The returned array must be malloced, assume caller calls free().
//*/
int* twoSum(int* nums, int numsSize, int target) {
	int* ret = (int*)malloc(2 * sizeof(int));
	int i = 0;
	int j = 0;
	for (i = 0; i<numsSize - 1; i++)
	{
		for (j = i + 1; j<numsSize; j++)
		{
			if (nums[i] + nums[j] == target)32
			{
				ret[0] = i;
				ret[1] = j;
				return ret;
			}
		}
	}

	return -1;
}

int main()
{
	int nums[] = { 2 , 7 , 11 , 15 };
	int sz = sizeof(nums) / sizeof(int );
	int target = 9;
	int *ret = twoSum(nums,sz,target);
	printf("%d , %d", *(ret + 0), *(ret + 1));
	free(ret);
	ret = NULL;

	system("pause");
	return 0;

}