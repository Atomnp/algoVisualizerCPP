#pragma once
//three way partitioning implementation of quick sort

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "../utils.h"
#include "../SortingInfo.h"

void q3sort(std::vector<int>& arr, int low, int high) {
	if (sortingInfo::stop)return;
	if (high <= low)return;
	//we have 3 pointers lt,i ,gt
	//the invarient is as follws
	//every thing to the left of lt is less than pivot element
	//everything to the right of gt is greater than pivot element
	//every element between lt and i is equal to pivot element
	//we maintain this invarient while performing partition

	int lt = low;
	int i = low + 1;
	int gt = high;
	sortingInfo::info.q3sort.lt = lt;
	sortingInfo::info.q3sort.gt = gt;
	while (i <= gt) {
		sortingInfo::info.q3sort.p = i;
		if (arr[i] < arr[lt]) {
			swap(arr, i, lt);
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			i++; lt++;
		}
		else if (arr[i] > arr[lt]) {
			swap(arr, i, gt);
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			gt--;
		}
		else {
			i++;
		}
		if (sortingInfo::stop)break;
		
	}
	q3sort(arr, low, lt - 1);
	q3sort(arr, gt + 1, high);
}
void qsort3Way(std::vector<int>& arr) {
	int low = 0;
	int high = arr.size() - 1;
	q3sort(arr, low, high);
	sortingInfo::sorted();
}


//int main() {
//	std::cout << "generating array....." << std::endl;
//	std::vector<int>arr = generateRandomArray(100, 100);
//	printArray(arr);
//	std::cout << "sorting...." << std::endl;
//	qsort3Way(arr);
//	std::cout << "sorted array" << std::endl;
//	printArray(arr);
//
//}