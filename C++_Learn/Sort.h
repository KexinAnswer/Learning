#pragma once
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>

void BubbleSort(std::vector<int>& arr) {
	int sz = arr.size();
	for (int i = 0; i < sz - 1; ++i) {
		for (int j = 0; j < sz - i - 1; ++j) {
			if (arr[j] > arr[j + 1]) {
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

void InsertSort(std::vector<int>& arr) {
	int sz = arr.size();

	for (int i = 1; i < sz; ++i) {
		int tmp = arr[i];
		int j;
		for (j = i - 1; j >= 0; --j) {
			if (tmp >= arr[j]) {
				break;
			}else {
				arr[j + 1] = arr[j];
			}
		}
		arr[j + 1] = tmp;
	}
}

void ShellInsert(std::vector<int>& arr, int gap) {
	int sz = arr.size();
	for (int i = gap; i < sz; ++i) {
		int k = arr[i];
		int j;
		for (j = i - gap; j >= 0; j-=gap) {
			if (arr[j] <= k) {
				break;
			}
			else {
				arr[j + gap] = arr[j];
			}
		}
		arr[j + gap] = k;
	}
}

void ShellSort(std::vector<int>& arr) {
	int gap = arr.size();
	while (1) {
		gap = gap / 3 + 1;
		ShellInsert(arr, gap);
		if (gap == 1) {
			break;
		}
	}
}

void SelectSort(std::vector<int>& arr) {
	int sz = arr.size();
	for (int i = 0; i < sz - 1; ++i) {
		int pos = i;
		for (int j = i+1; j < sz; ++j) {
			if (arr[pos] > arr[j]) {
				pos = j;
			}
		}

		std::swap(arr[i], arr[pos]);
	}
}

void AdjustDown(std::vector<int>& arr,int sz, int root) {
	int left = root * 2 + 1;
	if (left >= sz) {
		return;
	}

	int right = left + 1;
	int max = left;
	if (right < sz && arr[right] > arr[left]) {
		max = right;
	}

	if (arr[root] >= arr[max]) {
		return;
	}

	std::swap(arr[root], arr[max]);
	AdjustDown(arr,sz, max);
}

void HeapSort(std::vector<int>& arr) {
	for (int i = (arr.size() - 2) / 2; i >= 0; --i) {
		AdjustDown(arr, arr.size(), i);
	}
	for (int i = 0; i < arr.size() - 1; ++i) {
		std::swap(arr[0], arr[arr.size() - i - 1]);
		AdjustDown(arr, arr.size() - 1 - i, 0);
	}
}

int Partion_1(std::vector<int>& arr, int left, int right) {
	int flag = right;
	int begin = left;
	int end = right;
	while (begin < end) {
		while (begin < end && arr[begin] < arr[right]) {
			begin++;
		}
		// 左边走不动了
		while (begin < end && arr[end] > arr[right]) {
			end--;
		}
		// 右边走不动了

		std::swap(arr[begin], arr[end]);
	}

	return begin;
}

int Partion_2(std::vector<int>& arr, int left, int right) {
	int begin = left;
	int end = right;
	int index = arr[right];
	while (begin < end) {
		while (begin < end && arr[begin] <= index) {
			begin++;
		}
		// 左边走完了
		// 将右边的坑填上
		arr[end] = arr[begin];
		while (begin < end && arr[end] >= index) {
			end--;
		}
		arr[begin] = arr[end];
	}
	arr[begin] = index;
	return begin;
}

int Partion_3(std::vector<int>& arr, int left, int right) {
	int index = left;
	for (int i = left; i < right; ++i) {
		if (arr[i] < arr[right]) {
			std::swap(arr[index], arr[i]);
			index++;
		}
	}
	std::swap(arr[index] , arr[right]);
	return index;
}

int PickMid(const std::vector<int>& arr, int left, int right) {
	int mid = left+ (right - left) / 2;
	if (arr[left] > arr[right] && arr[left] > arr[mid]) {
		if (arr[mid] > arr[right]) {
			return mid;
		}
		else {
			return right;
		}
	}
	else if (arr[right] > arr[left] && arr[right] > arr[mid]) {
		if (arr[mid] > arr[left]) {
			return mid;
		}
		else {
			return left;
		}

	}
	else {
		if (arr[left] > arr[right]) {
			return left;
		}
		else {
			return right;
		}
	}
}

void _QucikSort(std::vector<int>& arr, int left, int right){
	if (left >= right) {
		return;
	}

	int pivot_index = PickMid(arr, left, right);
	std::swap(arr[pivot_index], arr[right]);
	int div;
	div = Partion_3(arr, left, right);
	_QucikSort(arr, left, div - 1);
	_QucikSort(arr, div + 1, right);

}

void _QucikSortNor(std::vector<int>& arr, int left, int right) {
	std::stack<int> s;
	s.push(right);
	s.push(left);
	int _left;
	int _right;
	while (!s.empty()) {
		_left = s.top();
		s.pop();
		_right = s.top();
		s.pop();

		if (_left >= _right) {
			continue;
		}

		int pivot = PickMid(arr, _left, _right);
		std::swap(arr[pivot], arr[_right]);

		int d = Partion_2(arr, _left, _right);
		s.push(_right);
		s.push(d+1);
		s.push(d - 1);
		s.push(_left);
	}
	
}


void Merge(std::vector<int>& arr, int left, int right, int mid, std::vector<int>& extra) {
	int size = right - left;
	int left_index = left;
	int right_index = mid;
	int extra_index = 0;
	while (left_index < mid && right_index < right) {
		if (arr[left_index] < arr[right_index]) {
			extra[extra_index] = arr[left_index];
			left_index++;
		}
		else {
			extra[extra_index] = arr[right_index];
			right_index++;
		}
		extra_index++;
	}

	while (left_index < mid) {
		extra[extra_index++] = arr[left_index++];
	}

	while (right_index < right) {
		extra[extra_index++] = arr[right_index++];
	}

	for (int i = 0; i < size; ++i) {
		arr[left+i] = extra[i];
	}
}

void _MergeSort(std::vector<int>& arr, int left, int right, std::vector<int>& extra) {
	if (right == left + 1){
		return;
	}
	if (left >= right) {
		return;
	}

	int mid = left + (right - left) / 2;

	_MergeSort(arr, left, mid, extra);
	_MergeSort(arr, mid, right, extra);

	Merge(arr, left, right, mid, extra);
}

void MergeSort(std::vector<int>& arr) {
	std::vector<int> extra(arr.size(), 0);
	_MergeSort(arr, 0, arr.size(), extra);
}

