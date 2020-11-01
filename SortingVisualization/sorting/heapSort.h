#pragma once


#include <iostream>
#include <vector>

#include <chrono>
#include <thread>
#include "../utils.h"
#include "../SortingInfo.h"
int maxIndex(std::vector<int>& data, int a, int b) {
	if (data[a] >= data[b])return a;
	return b;
}
void swim(std::vector<int>& arr, int index) {
	if (index == 0) return;
	while ((arr[index] > arr[(index - 1) / 2]) and index > 0) {

		swap(arr, index, (index - 1) / 2);
		if (sortingInfo::stop)return;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		index = (index - 1) / 2;
	}
}

//need to optimize this some time later
void sink(std::vector<int>& data, int currentIndex) {
	int index = 0;
	while ((2 * index + 2) <= currentIndex and (data[index] < data[2 * index + 1] or data[index] < data[2 * index + 2])) {

		//if there is no item in 2*index +2 and index and 2*index+1 is greater than the element to sink
		if (2 * index + 2 == currentIndex and data[2 * index + 1] > data[index]) {
			swap(data, index, 2 * index + 1);
			break;
		}
		// if there is no item in 2 * index + 2 and index and 2 * index + 1 is less than the element to sink
		if (2 * index + 2 == currentIndex and data[2 * index + 1] <= data[index]) {
			break;
		}
		//if both there are element at both 2*index +1 and 2*index+2
		int maxIn = maxIndex(data, 2 * index + 1, 2 * index + 2);
		swap(data, index, maxIn);
		if (sortingInfo::stop)return;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		index = maxIn;
	}

}
void moveMaxToLast(std::vector<int>& arr, int currentIndex) {
	swap(arr, 0, currentIndex - 1);
	sink(arr, currentIndex - 1);
}
void heapify(std::vector<int>& arr) {
	for (int i = 1; i < arr.size(); i++) {
		if (sortingInfo::stop)return;
		swim(arr, i);
	}
}
void heapSort(std::vector<int>& arr) {
	heapify(arr);
	for (int last = arr.size(); last > 0; last--) {
		if (sortingInfo::stop)break;
		moveMaxToLast(arr, last);
	}
	sortingInfo::sorted();
}

//int main() {
//	std::vector<int> arr = generateRandomArray(10);
//	std::cout << " unsorted array " << std::endl;
//	printArray(arr);
//
//	std::cout << "heapified array" << std::endl;
//	heapify(arr);
//	printArray(arr);
//
//	sort(arr);
//	std::cout << "sorted array" << std::endl;
//	printArray(arr);
//
//}