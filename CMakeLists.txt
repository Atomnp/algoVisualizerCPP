cmake_minimum_required (VERSION 3.1)
project (SortingViualizer)

set(CMAKE_CXX_STANDARD 14)

#to setup sdl, chek cmake_modules di
#that filein cmake just search about libraries in probable location 
#and set variables so that we can work easily here
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)


set(INCLUDE_DIRECTORIES
  ${SDL2_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/SortingVisualization/vendors/imgui
  ${GLEW_INCLUDE_DIRS})

  set(LINK_LIBRARIES 
    ${OPENGL_LIBRARIES} 
    ${SDL2_LIBRARY}
    ${GLEW_LIBRARIES}
    )

include_directories(${INCLUDE_DIRECTORIES})

# we should put our source file which we want to build manually
set (SOURCE_FILES 
    ${CMAKE_SOURCE_DIR}/SortingVisualization/main.cpp
    ${CMAKE_SOURCE_DIR}/SortingVisualization/vendors/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/SortingVisualization/vendors/imgui/imgui_impl_sdl.cpp
    ${CMAKE_SOURCE_DIR}/SortingVisualization/vendors/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/SortingVisualization/vendors/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/SortingVisualization/vendors/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/SortingVisualization/vendors/imgui/imgui_impl_opengl3.cpp
   )

add_executable(SortingVisualizer ${SOURCE_FILES})
target_link_libraries(SortingVisualizer ${LINK_LIBRARIES})



