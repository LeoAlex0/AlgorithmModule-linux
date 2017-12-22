cmake_minimum_required(VERSION 3.10)

project(ALGORITHM_MODULE)

if (CMAKE_BUILD_TYPE STREQUAL Debug) 
	set(DEBUG YES)
else()
	set(DEBUG NO)
endif()

include_directories(${ALGORITHM_MODULE_SOURCE_DIR}/include)
link_directories(${ALGORITHM_MODULE_SOURCE_DIR}/lib)

add_subdirectory(src)
