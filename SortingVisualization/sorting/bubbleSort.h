#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "../SortingInfo.h"
#include "../utils.h"

//extern int sortedRight;

void bubbleSort(std::vector<int>& arr) {
	
	printf("in bubble sort");
	for (int i = 0; i < arr.size() and !sortingInfo::stop; i++) {
		//for graphics
		sortingInfo::info.bsort.sortedRight = arr.size() - i;

;		for (int j = 0; j < (arr.size() - i - 1) and !sortingInfo::stop; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr, j, j + 1);
				std::this_thread::sleep_for(std::chrono::milliseconds((int)sortingInfo::speed));
			}
			
		}
	}
	sortingInfo::sorted();
}

//unit test
//int main() {
//	std::cout << "unsorted array" << std::endl;
//	auto arr = generateRandomArray(10);
//	printArray(arr);
//	sort(arr);
//	std::cout << "sorted array" << std::endl;
//	printArray(arr);
//}