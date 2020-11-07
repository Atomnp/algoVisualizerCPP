#pragma once


#include <iostream>
#include <vector>
#include <chrono>
#include<thread>

#include "../SortingInfo.h"
#include "../utils.h"

void insertionSort(std::vector<int>& arr) {
	for (int i = 1; i < arr.size(); i++) {
		if (sortingInfo::stop)break;
		sortingInfo::info.isort.sortedLeft = i;
		int j = i;
		while (j > 0 and arr[j] < arr[j - 1]) {
			sortingInfo::info.isort.currentPointer = j-1;
			swap(arr, j, j - 1);
			std::this_thread::sleep_for(std::chrono::milliseconds(sortingInfo::speed));
			j--;
		}
	}
	sortingInfo::sorted();
}
//unit test for selection sort
//int main() {
//	auto arr = generateRandomArray(20);
//	std::cout << "unsorted array" << std::endl;
//	printArray(arr);
//	std::cout << "sorted array" << std::endl;
//	sort(arr);
//	printArray(arr);
//}