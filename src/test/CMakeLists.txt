SET(EXECUTABLE_OUTPUT_PATH ${ALGORITHM_MODULE_SOURCE_DIR}/bin)

aux_source_directory (. SRC_LIST)

if (LIBRARY_TYPE STREQUAL STATIC)
	FOREACH(source_file ${SRC_LIST})
		string (REGEX REPLACE "./" "" source_file "${source_file}")
		STRING (REGEX REPLACE "_main.cpp" "" bin_name "${source_file}")
		STRING (REGEX REPLACE "_main.c" "_c" bin_name "${bin_name}")
		ADD_EXECUTABLE ("${bin_name}" "${source_file}")
		TARGET_LINK_LIBRARIES ("${bin_name}" algorithm_module)
	ENDFOREACH()
endif()
