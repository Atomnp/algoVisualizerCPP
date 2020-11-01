#include <iostream>
#include <vector>
#include "../commonHeaders/utils.h"

//can sort only single digit numbers but in linear time
void countingSort(std::vector<int>& arr) {
	int count[10];
	memset(count, 0, sizeof count);
	std::vector<int >output = std::vector<int>(arr.size());

	for (int i = 0; i < arr.size(); i++) {
		count[arr[i]]++;
	}
	for (int i = 1; i < 10; i++) {
		count[i] = count[i] + count[i - 1];
	}
	for (int i = 0; i < arr.size(); i++) {
		output[count[arr[i]]-- - 1] = arr[i];

	}
	arr = output;
}
int main() {
	std::vector<int>arr = generateRandomArray(10, 9);//10 nubers between 0 to 9
	std::cout << "original array" << std::endl;
	printArray(arr);
	std::cout << "sorted array" << std::endl;
	countingSort(arr);
	printArray(arr);
}