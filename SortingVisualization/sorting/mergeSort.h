#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include "../utils.h" //swap() and generateRandomArray()
#include "../SortingInfo.h"


void merge(std::vector<int>& arr, int high, int low, int mid) {
	std::vector<int>aux = arr;
	int i = low;
	int m = mid + 1;
	int k = low;
	sortingInfo::info.mSort.left = i;
	sortingInfo::info.mSort.right = high;
	while (i <= mid or m <= high) {
		if (i > mid) {
			arr[k++] = aux[m++];
			continue;
		}
		if (m > high) {
			arr[k++] = aux[i++];
			continue;
		}
		if (aux[i] <= aux[m]) {
			arr[k++] = aux[i++];
		}
		else {
			arr[k++] = aux[m++];
		}
		if (sortingInfo::stop)return;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		
	}
}

void sort(std::vector<int>& arr, int high, int low) {
	if (sortingInfo::stop)return;
	if (high == low) {
		return;
	}
	int mid = (high + low) / 2;
	//sort function takes high then low
	sort(arr, mid, low);
	sort(arr, high, mid + 1);
	merge(arr, high, low, mid);

}

void mergeSort(std::vector<int>& arr) {

	int low = 0;
	int high = arr.size() - 1;
	sort(arr, high, low);
	
	sortingInfo::sorted();

}

