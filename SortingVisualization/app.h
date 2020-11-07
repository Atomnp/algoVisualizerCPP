#pragma once

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <iostream>

#define SDL_MAIN_HANDLED
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

class App {
private:
	SDL_GLContext gl_context;
	SDL_Renderer* renderer;
	SDL_Window* window;

public:
	void run();

	App() {
		// Setup SDL
		// (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
		// depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
		{
			printf("Error: %s\n", SDL_GetError());
			throw "SDL initialization failed!";
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
		window = SDL_CreateWindow("Greatest Visualizer Of all Time", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);

		gl_context = SDL_GL_CreateContext(window);

		SDL_GL_MakeCurrent(window, gl_context);
		SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
		SDL_GL_SetSwapInterval(1); // Enable vsync

		//initialize OpenGL loader
		bool err = glewInit() != GLEW_OK;

		if (err)
		{
			fprintf(stderr, "Failed to initialize OpenGL loader!\n");
			throw "Failed to initialize OpenGL loader(glew)";
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

		//setup SDL renderer
		renderer = NULL;
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	}

	~App() {
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		SDL_GL_DeleteContext(gl_context);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

private:
	void render() {
		// Rendering     
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderPresent(renderer);
	}

	void clearScreen() {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	}

	void handleEvents(bool& done) {
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

	}

};