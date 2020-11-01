
#include <iostream>
#include <vector>

#include <chrono>
#include <thread>
#include "../utils.h"
#include "../SortingInfo.h"
#include "quickSort.h"
#undef main

int maxIndex(std::vector<int>& data, int a, int b) {
	if (data[a] >= data[b])return a;
	return b;
}
void swim(std::vector<int>& arr, int index) {
	if (index == 0) return;
	while ((arr[index] > arr[(index-1) / 2]) and index > 0) {

		swap(arr, index, (index-1) / 2);
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));
		index = (index-1) / 2;
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
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));
		index = maxIn;
	}

}
void moveMaxToLast(std::vector<int>& arr, int currentIndex) {
	swap(arr, 0, currentIndex - 1);
	//std::this_thread::sleep_for(std::chrono::milliseconds(50));
	sink(arr, currentIndex - 1);
}
void heapify(std::vector<int>& arr) {
	for (int i = 1; i < arr.size(); i++) {
		swim(arr, i);
		/*printf("heapified at index %d", i);
		printArray(arr);*/
	}
	
}
void heapSort(std::vector<int>& arr) {
	heapify(arr);
	/*printf("heapified array");
	printArray(arr);*/
	for (int last = arr.size(); last > 0; last--) {
		moveMaxToLast(arr, last);
	}
}

int main() {
	// {1,6,6,17,35,44,53,55,57,58,61,63,63,63,68,71,76,74,78,80,90,91,95,95,98}
	for (int i = 0; i < 1000; i++) {
		std::vector<int> arr = generateRandomArray(50);
		auto ref = arr;
		auto ref2 = arr;

		quickSort(ref);
		heapSort(arr);

		for (int i = 0; i < arr.size(); i++) {
			if (arr[i] != ref[i])
			{
				printArray(ref2);
				printf("doesn't work");
				break;
			}
		}
		
	}
	printf("every thing works");


	//std::vector<int >arr= {54, 97, 86, 77, 38, 14, 88, 21, 19, 7};
	//std::cout << " unsorted array " << std::endl;
	//printArray(arr);

	//std::cout << "heapified array" << std::endl;
	//heapify(arr);
	//printArray(arr);

	//heapSort(arr);
	//std::cout << "sorted array" << std::endl;
	//printArray(arr);

	return 1;
}