cmake_minimum_required(VERSION 3.0)

project(ALGORITHM_MODULE)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR
	CMAKE_BUILD_TYPE STREQUAL "None")
	set(LIBRARY_TYPE STATIC)
	add_definitions("-g")
else()
	set(LIBRARY_TYPE SHARED)
	add_definitions("-O2")
endif()

include_directories(${ALGORITHM_MODULE_SOURCE_DIR}/include)
link_directories(${ALGORITHM_MODULE_SOURCE_DIR}/lib)

add_subdirectory(src)
