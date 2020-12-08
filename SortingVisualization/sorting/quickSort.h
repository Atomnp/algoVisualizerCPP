#pragma once
//most slow implementation of the quick sort algorithm

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "../utils.h"
#include "../SortingInfo.h"

//int lt;
//int gt;

int  partition(std::vector<int>& arr, int low, int high) {
	int pivotElm = arr[low];
	
	
	int i = low + 1;
	int j = high;
	sortingInfo::info.qsort.leftIndex = i;
	sortingInfo::info.qsort.rightIndex = j;
	sortingInfo::info.qsort.pivotIndex = low;
	sortingInfo::info.qsort.ptr1 = i;
	sortingInfo::info.qsort.ptr2 = j;
	while (true) {
		while (arr[i] < pivotElm) {
			if (i == high) break;
			i++;
			sortingInfo::info.qsort.ptr1 = i;
			if(sortingInfo::teachingMode)std::this_thread::sleep_for(std::chrono::milliseconds(sortingInfo::speed));

		}
		while (arr[j] > pivotElm) {
			if (j == low)break;
			j--;
			sortingInfo::info.qsort.ptr2 = j;
			if(sortingInfo::teachingMode)std::this_thread::sleep_for(std::chrono::milliseconds(sortingInfo::speed));

		}		
		
		
		if (i >= j) {
			swap(arr, low, j);
			std::this_thread::sleep_for(std::chrono::milliseconds(sortingInfo::speed));
			return j;

		}
		swap(arr, i, j); i++; j--;
		if (sortingInfo::stop) {
			return -1;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(sortingInfo::speed));
	}
}
void qsort(std::vector<int>& arr, int low, int high) {
	if (sortingInfo::stop)return;
	if (high <= low)return;
	int index = partition(arr, low, high);
	if (index == -1)return;
	qsort(arr, low, index - 1);
	qsort(arr, index + 1, high);
}
void quickSort(std::vector<int>& arr) {
	int low = 0;
	int high = arr.size() - 1;
	qsort(arr, low, high);
	sortingInfo::sorted();
}


//int main() {
//	std::cout << "generating array....." << std::endl;
//	std::vector<int>arr = generateRandomArray(10000000,10000000);
//	//printArray(arr);
//	std::cout << "sorting...." << std::endl;
//	sort(arr);
//	std::cout << "sorted array" << std::endl;
//	//printArray(arr);
//
//	//partition test
//	/*std::vector<int>arr = { 2,1 };
//	int index = partition(arr, 0, 1);*/
//
//}
