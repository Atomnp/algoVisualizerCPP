#pragma once

#include <iostream>
#include <vector>
//for graphics
#include <chrono>
#include <thread>
#include "../SortingInfo.h"

#include "../utils.h"
void countingSort(std::vector<int>& arr,int exp) {
	int count[10];
	memset(count, 0, sizeof count);
	std::vector<int >output = std::vector<int>(arr.size());

	for (int i = 0; i < arr.size(); i++) {
		if (sortingInfo::stop)return;
		count[arr[i]/exp%10]++;
	}
	for (int i = 1; i < 10; i++) {
		if (sortingInfo::stop)return;
		count[i] = count[i] + count[i - 1];
	}
	//this is reversed to make it stable sort otherwise radix sort with counting sort wont work
	//try with foreward loop if wanna see how it looks
	for (int i=arr.size()-1; i >=0; i--) {
		if (sortingInfo::stop)return;
		
		output[count[arr[i] / exp % 10]-- -1] = arr[i];
		
	}
	arr = output;
}

int countDigit(int n) {
	int result=0;
	for (int i = 1;; i = i * 10) {
		result++;
		if (n / i == 0)return result-1;
	}
}

int findMax(std::vector<int>arr) {
	int max = arr[0];
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}

void radixSort(std::vector<int>&arr) {
	int max = findMax(arr);
	int noOfDigit = countDigit(max);
	int exp = 1;
	for (int i = 1; i <= noOfDigit; i++) {
		
		countingSort(arr, exp );
		if (sortingInfo::stop)break;
		std::this_thread::sleep_for(std::chrono::milliseconds(20*sortingInfo::speed));
		
		
		exp *= 10;
	}
	sortingInfo::sorted();
}

//int main() {
//	//count digit test
//	/*int a = 355;
//	int res = countDigit(a);
//	std::cout << res << std::endl;*/
//
//	//counting sort test
//	/*std::vector<int>arr = { 999,742,201,661,100,435,222,333,445,653,184 };
//	std::cout << "original array" << std::endl;
//	printArray(arr);
//	std::cout << "sorted array" << std::endl;
//	countingSort(arr,10);
//	printArray(arr);*/
//
//	//radix sort test
//	std::vector<int>arr =generateRandomArray(1000,1000);
//	std::cout << "original array" << std::endl;
//	printArray(arr);
//	std::cout << "sorted array" << std::endl;
//	radixSort(arr);
//	printArray(arr); 
//
//}