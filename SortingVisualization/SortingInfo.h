#pragma once

struct BubbleSort {
	int currentPointer;
	// sortedRight represents index after which the array is in sorted array
	int sortedRight;
};
struct QuickSort {
	int leftIndex;
	int rightIndex;
	int pivotIndex;
};
struct MergeSort {
	int left;
	int right;
};
struct InsertionSort {
	int currentPointer;
	int sortedLeft;
};
struct ShellSort {
	int knuthIndex;
	int currentPointer;
	int x;
};
struct SelectionSort {
	int currentPointer;
	int sortedLeft;
	int s1;
	int s2;
};
struct Qsort3Way {
	int lt;
	int gt;
	int p;
};
struct HeapSort {
	int sortedRight;
};
enum class SortType
{
	BUBBLE_SORT=1,
	QUICK_SORT,
	MERGE_SORT,
	INSERTION_SORT,
	SHELL_SORT,
	SELECTION_SORT,
	RADIX_SORT,
	HEAP_SORT,
	QSORT3WAY
};
union SortingInfo{
public:
	MergeSort mSort;
	QuickSort qsort;
	BubbleSort bsort;
	InsertionSort isort;
	ShellSort shSort;
	SelectionSort ssort;
	Qsort3Way q3sort;
	HeapSort hsort;

};
namespace sortingInfo {
	 SortingInfo info;
	 SortType type;
	 bool stop = false;
	 std::thread sortingThread;
	 bool sortThreadActive = false;
	 bool sortingMenu = false;
	 int speedFactor = 1;

	 void sorted() {
		printf("finished or closed sorting\n");
		sortingThread.detach();
		sortThreadActive = false;
		/*sortingMenu = true;*/
	 }
	 void start() {
		 stop = false;
		 sortingInfo::sortThreadActive = true;
		 sortingInfo::sortingMenu = false;
	 }
	 void makeRedIf(bool conditions, SDL_Renderer*&renderer) {
		 if (conditions)
		 {
			 SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);

		 }
	 }
}
