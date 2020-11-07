#include "app.h"
// Main code
int main()
{
	try {
		App app;
		app.run();
	}
	catch (...) {
		std::cout << "Something went wrong!" << std::endl;
	}
	return 0;
}

void App::run() {
	//for array to be sorted
	int prevNumberOfItems = 100;
	int numberOfItems = 100;
	std::vector<int>arr = generateRandomArray(numberOfItems);
	const int gap = 2;
	int rectWidth = (SCREEN_WIDTH - SORTING_MENU_WIDTH) / (numberOfItems + gap) - gap;
	int position = 0;

	// Main loop
	bool done = false;
	float speedFactor = 1;
	while (!done)
	{
		handleEvents(done);
		clearScreen();

		//Shuffle if the number of elements is changed
		if (prevNumberOfItems != numberOfItems) {
			arr = generateRandomArray(numberOfItems);
			rectWidth = (SCREEN_WIDTH - 250) / (numberOfItems + gap) - gap;
			prevNumberOfItems = numberOfItems;
		}

		position = 0;
		SDL_Rect rect;
		int radixSpecial = 1;
		if (sortingInfo::type == SortType::RADIX_SORT )radixSpecial = 987654;
		for (int i = 0; i < numberOfItems; i++) {
			getRectangle(rect, position, SCREEN_HEIGHT - 4 * arr[i]/radixSpecial - 175, rectWidth, 4 * arr[i]/radixSpecial);

			if (sortingInfo::sortThreadActive) {
				switch (sortingInfo::type) {
				case SortType::BUBBLE_SORT:
					sortingInfo::makeRedIf(i >= sortingInfo::info.bsort.sortedRight, renderer);
					break;
				case SortType::QUICK_SORT:
					sortingInfo::makeRedIf(
						i >= sortingInfo::info.qsort.leftIndex and
						i <= sortingInfo::info.qsort.rightIndex,
						renderer
					);
					if (i == sortingInfo::info.qsort.pivotIndex) {
						//green color for pivot element
						SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
					}

					break;
				case SortType::MERGE_SORT:
					sortingInfo::makeRedIf(
						i >= sortingInfo::info.mSort.left and
						i <= sortingInfo::info.mSort.right, renderer
					);
					break;
				case SortType::INSERTION_SORT:
					sortingInfo::makeRedIf(i <= sortingInfo::info.isort.sortedLeft, renderer);
					if (i == sortingInfo::info.isort.currentPointer) {
						//green color for current index
						SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
					}
					break;
				case SortType::SHELL_SORT:
					sortingInfo::makeRedIf(i % sortingInfo::info.shSort.knuthIndex == 0, renderer);
					if (i == sortingInfo::info.isort.currentPointer) {
						//green color for current index
						SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
					}
					break;
				case SortType::SELECTION_SORT:
					sortingInfo::makeRedIf(i <= sortingInfo::info.ssort.sortedLeft, renderer);
					if (i == sortingInfo::info.ssort.currentPointer) {
						//green color for current index
						SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
					}
					break;
				case SortType::HEAP_SORT:
					sortingInfo::makeRedIf(i >= sortingInfo::info.hsort.sortedRight, renderer);

					break;
				case SortType::QSORT3WAY:
					sortingInfo::makeRedIf(
						i >= sortingInfo::info.q3sort.lt and
						i <= sortingInfo::info.q3sort.gt,
						renderer
					);
					if (i == sortingInfo::info.q3sort.lt or i== sortingInfo::info.q3sort.gt) {
						//green color for pivot element
						SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
					}
					if (i == sortingInfo::info.q3sort.p) {
						//green color for pivot element
						SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
					}

					break;
				default:
					break;

				}
			}
			SDL_RenderFillRect(renderer, &rect);
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			position += gap + rectWidth;

		}

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		//store the window configuration
		ImGuiWindowFlags windowFlags = 0;
		windowFlags |= ImGuiWindowFlags_NoResize;

		static int CurrentSort = 0;

		ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH - SORTING_MENU_WIDTH, 0));
		ImGui::SetNextWindowSize(ImVec2(SORTING_MENU_WIDTH, SORTING_MENU_HEIGHT));

		ImGui::Begin("SORTING", NULL, windowFlags);
		const char* items[] = {
			"Bubble Sort",
			"Merge Sort",
			"Quick Sort",
			"Insertion Sort",
			"Shell Sort",
			"Selection Sort",
			"Radix Sort",
			"Heap Sort",
			"Quick Sort 3 way Partition"
		};
		ImGui::ListBox("", &CurrentSort, items, IM_ARRAYSIZE(items), IM_ARRAYSIZE(items));
		ImGui::End();

		//ImGui UI
		{
			ImGui::SetNextWindowPos(ImVec2(0, SCREEN_HEIGHT - CONTROL_MENU_HEIGHT));
			ImGui::SetNextWindowSize(ImVec2(CONTROL_MENU_WIDTH, CONTROL_MENU_HEIGHT));

			ImGui::Begin("Controller", NULL, windowFlags);
			if (ImGui::Button("Start")) {
				switch (CurrentSort) {
				case 0:
					if (!sortingInfo::sortThreadActive) {
						sortingInfo::start();
						sortingInfo::type = SortType::BUBBLE_SORT;
						sortingInfo::sortingThread = std::thread(bubbleSort, std::ref(arr));
					}
				case 1:
					if (!sortingInfo::sortThreadActive) {
						sortingInfo::start();
						sortingInfo::type = SortType::MERGE_SORT;
						sortingInfo::sortingThread = std::thread(mergeSort, std::ref(arr));
					}
				case 2:
					if (!sortingInfo::sortThreadActive) {
						sortingInfo::start();
						sortingInfo::type = SortType::QUICK_SORT;
						sortingInfo::sortingThread = std::thread(quickSort, std::ref(arr));
					}
				case 3:
					if (!sortingInfo::sortThreadActive) {
						sortingInfo::start();
						sortingInfo::type = SortType::INSERTION_SORT;
						sortingInfo::sortingThread = std::thread(insertionSort, std::ref(arr));
					}
				case 4:
					if (!sortingInfo::sortThreadActive) {
						sortingInfo::start();
						sortingInfo::type = SortType::SHELL_SORT;
						sortingInfo::sortingThread = std::thread(shellSort, std::ref(arr));
					}
				case 5:
					if (!sortingInfo::sortThreadActive) {
						sortingInfo::start();
						sortingInfo::type = SortType::SELECTION_SORT;
						sortingInfo::sortingThread = std::thread(selectionSort, std::ref(arr));
					}
				case 6:
					if (!sortingInfo::sortThreadActive) {
						for (int i = 0; i < arr.size(); i++) {
							arr[i] = arr[i] * 987654;
						}
						sortingInfo::start();
						sortingInfo::type = SortType::RADIX_SORT;
						sortingInfo::sortingThread = std::thread(radixSort, std::ref(arr));
					}
				case 7:
					if (!sortingInfo::sortThreadActive) {
						sortingInfo::start();
						sortingInfo::type = SortType::HEAP_SORT;
						sortingInfo::sortingThread = std::thread(heapSort, std::ref(arr));
					}
				case 8:
					if (!sortingInfo::sortThreadActive) {
						sortingInfo::start();
						sortingInfo::type = SortType::QSORT3WAY;
						sortingInfo::sortingThread = std::thread(qsort3Way, std::ref(arr));
					}
				}

			}
			ImGui::SameLine();
			if (ImGui::Button("RESET"))
			{

				if (sortingInfo::sortThreadActive) {
					sortingInfo::stop = true;
					while (sortingInfo::sortThreadActive) {
						//do nothing and wait
						std::cout << "aaa" << std::endl;
					}

				}

				arr = generateRandomArray(numberOfItems);
				if (sortingInfo::type == SortType::RADIX_SORT) {
					for (int i = 0; i < arr.size();i++) {
						arr[i] = arr[i] * 987654;
					}
				}

			}
			//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			if (!sortingInfo::sortThreadActive) {
				ImGui::SliderInt("Number Of Items To Sort", &numberOfItems, 0, 300);
			}
			
			
			ImGui::SliderFloat("SPEED in Times", &speedFactor, 0.1f, 10.0f);
			sortingInfo::speed = (int)(1.0 / speedFactor * 50);

			ImGui::End();
		}

		render();
	}

}