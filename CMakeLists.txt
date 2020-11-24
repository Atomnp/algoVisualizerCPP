cmake_minimum_required (VERSION 3.1)
project (SortingViualizer)

set(CMAKE_CXX_STANDARD 14)

#to setup sdl, chek cmake_modules dir
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

find_package(SDL2 REQUIRED)
# look for glew relative to the "GLEW" environment variable path
# Need to set GLEW_INCLUDE_DIR and GLEW_LIBRARY_RELEASE
IF(NOT(APPLE))
  set(GLEW_INCLUDE_DIR $ENV{GLEW}/include)
  set(GLEW_LIBRARY_RELEASE $ENV{GLEW}/lib/Release/Win32/glew32.lib)
  find_package(GLEW REQUIRED)
ENDIF()

find_package(OpenGL REQUIRED)
set(INCLUDE_DIRECTORIES
  ${SDL2_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/SortingVisualization/vendors/imgui)
set(LINK_LIBRARIES ${OPENGL_LIBRARIES} ${SDL2_LIBRARY})

IF(NOT(APPLE))
	list(APPEND INCLUDE_DIRECTORIES ${GLEW_INCLUDE_DIRS})
  list(APPEND LINK_LIBRARIES ${GLEW_LIBRARIES})
ENDIF()

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



