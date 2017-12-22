cmake_minimum_required(VERSION 3.0)

project(ALGORITHM_MODULE)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
	set(LIBRARY_TYPE STATIC)
else()
	set(LIBRARY_TYPE SHARED)
endif()

include_directories(${ALGORITHM_MODULE_SOURCE_DIR}/include)
link_directories(${ALGORITHM_MODULE_SOURCE_DIR}/lib)

add_subdirectory(src)
