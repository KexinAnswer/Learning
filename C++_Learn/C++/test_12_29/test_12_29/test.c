#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

//给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
//你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
//示例 :
//给定 nums = [2, 7, 11, 15], target = 9
//
//因为 nums[0] + nums[1] = 2 + 7 = 9
//所以返回[0, 1]
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