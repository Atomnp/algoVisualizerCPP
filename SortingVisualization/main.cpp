#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <vector>
#include <thread>

#include "./sorting/bubbleSort.h"
#include "./sorting/mergeSort.h"
#include "./sorting/quickSort.h"
#include "./sorting/insertionSort.h"
#include "./sorting/radixSort.h"
#include "./sorting/selectionSort.h"
#include "./sorting/heapSort.h"
#include "./sorting/shellSort.h"
#include "./sorting/qsort3way.h"

#include "utils.h"
#include "SortingInfo.h"

static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 720;


static const int CONTROL_MENU_WIDTH = SCREEN_WIDTH;
static const int CONTROL_MENU_HEIGHT = 150;

static const int SORTING_MENU_WIDTH = 200;
static const int SORTING_MENU_HEIGHT = SCREEN_HEIGHT - CONTROL_MENU_HEIGHT;


// Main code
int main(int, char**)
{
    // Setup SDL
    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Greatest Visualizer Of all Time", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,SCREEN_HEIGHT, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_GL_SetSwapInterval(1); // Enable vsync

    //initialize opengl loader
    bool err = glewInit() != GLEW_OK;

    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    //setup sdl renderer
    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //for array to be sorted
    int prevNumberOfItems = 100;
    int numberOfItems = 100;
    std::vector<int>arr = generateRandomArray(numberOfItems);
    const int gap = 2;
    int rectWidth = (SCREEN_WIDTH-SORTING_MENU_WIDTH) / (numberOfItems + gap) - gap;
    int position = 0;


    // Main loop
    bool done = false;
    while (!done)
    {
       
        if (prevNumberOfItems != numberOfItems) {
            arr = generateRandomArray(numberOfItems);
            rectWidth = (SCREEN_WIDTH - 250) / (numberOfItems + gap) - gap;
            prevNumberOfItems = numberOfItems;
        }
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                
                sortingInfo::stop = true;
                while (sortingInfo::sortThreadActive) {
                    //wait for sorting thread to finish
                    std::cout << "waiting up" << std::endl;
                }
                done = true;
            }
               
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
            {
                
                sortingInfo::stop = true;
                while (sortingInfo::sortThreadActive) {
                    //wait for sorting thread to finish
                    std::cout << "waiting down" << std::endl;
                }
                done = true;
            }
        }

        SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        position = 0;
        SDL_Rect rect;
        for (int i = 0; i < numberOfItems; i++) {
            getRectangle(rect, position, SCREEN_HEIGHT - 4 * arr[i]-175, rectWidth, 4 * arr[i]);

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
                    sortingInfo::makeRedIf(i%sortingInfo::info.shSort.knuthIndex==0 , renderer);
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
        
        static int CurrentSort = 2;
        ImGui::SetNextWindowPos(ImVec2(SCREEN_WIDTH-SORTING_MENU_WIDTH,0));
        ImGui::SetNextWindowSize(ImVec2(SORTING_MENU_WIDTH,SORTING_MENU_HEIGHT));
        ImGui::Begin("SORTING",NULL,windowFlags);
            const char* items[] = { "Bubble Sort", "Merge Sort", "Quick Sort","Insertion Sort","Shell Sort","Selection Sort", "Radix Sort","Heap Sort", "QUick SOrt 3 way Par"};
            
            ImGui::ListBox("", &CurrentSort, items, IM_ARRAYSIZE(items), IM_ARRAYSIZE(items));
        ImGui::End();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        
        //if (show_demo_window)
        //    ImGui::ShowDemoWindow(&show_demo_window);


        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            ImGui::SetNextWindowPos(ImVec2(0, SCREEN_HEIGHT-CONTROL_MENU_HEIGHT));
            ImGui::SetNextWindowSize(ImVec2(CONTROL_MENU_WIDTH, CONTROL_MENU_HEIGHT));
            
           
            ImGui::Begin("Controller",NULL,windowFlags);                          // Create a window called "Hello, world!" and append into it.
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
                            sortingInfo::type = SortType::SELECTION_SORT    ;
                            sortingInfo::sortingThread = std::thread(selectionSort, std::ref(arr));
                        }
                    case 6:
                        if (!sortingInfo::sortThreadActive) {
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
            if (ImGui::Button("RESET") )
            {
               
                if (sortingInfo::sortThreadActive) {
                    sortingInfo::stop = true;
                    while (sortingInfo::sortThreadActive) {
                        //do nothing and wait
                        std::cout << "aaa" << std::endl;
                    }
                  
                }
                
                arr = generateRandomArray(numberOfItems);
                
            }
            //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            if (!sortingInfo::sortThreadActive) {
                ImGui::SliderInt("Number Of Items To Sort", &numberOfItems, 0, 300);
            }
           
            ImGui::End();
        }

        // Rendering     
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
   

    return 0;
}
