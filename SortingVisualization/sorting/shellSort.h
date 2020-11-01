#pragma once
//knuth pattern for shellsort is given by formula
//h=h*3+1;
//1,4,13,40,121
#pragma once
#include <iostream>
#include<vector>
#include <chrono>
#include <thread>
#include "../utils.h"
#include "../SortingInfo.h"

void shellSort(std::vector<int>& arr) {
	int highest = 1;
	while (3 * highest + 1 < arr.size() - 1) {
		highest = 3 * highest + 1;
	}
	while (highest >= 1) {
		//for graphics
		//sortingInfo::info.shSort.knuthIndex = highest;
		if (sortingInfo::stop)break;

		for (int i = highest; i < arr.size(); i++) {
			//for graphics
			sortingInfo::info.shSort.knuthIndex = i;
			int j = i;
			while (j >= highest and arr[j] < arr[j - highest]) {				
				swap(arr, j, j - highest);
				//for graphics
				if (sortingInfo::stop)break;

				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				j = j - highest;
				//for graphics
				sortingInfo::info.shSort.currentPointer = j;

			}
		}
		highest = (highest - 1) / 3;
	}
	sortingInfo::sorted();
}
//int main() {
//	std::cout << "generating array" << std::endl;
//	std::vector<int> arr = generateRandomArray(20);
//	std::cout << "unsorted array" << std::endl;
//	//printArray(arr);
//	sort(arr);
//	std::cout << "sorted" << std::endl;
//	//printArray(arr);
//
//}