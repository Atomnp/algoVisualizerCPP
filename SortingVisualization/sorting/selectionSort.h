#pragma once


#include <iostream>
#include <vector>

//for graphics
#include <chrono>
#include <thread>
#include "../SortingInfo.h"

#include "../utils.h"

void selectionSort(std::vector<int>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		//for graphics
		sortingInfo::info.ssort.sortedLeft = i;
		if (sortingInfo::stop)break;

		int minIndex = i;
		for (int j = i + 1; j < arr.size(); j++) {
			sortingInfo::info.ssort.currentPointer = j;
			//for graphics
			if (sortingInfo::stop)break;

			std::this_thread::sleep_for(std::chrono::milliseconds(sortingInfo::speed));

			if (arr[j] < arr[minIndex])minIndex = j;
		}
		swap(arr, i, minIndex);
		
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