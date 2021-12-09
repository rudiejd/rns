cmake_minimum_required(VERSION 3.14)
project(
	rns
	VERSION 0.1
	DESCRIPTION "Implementation of a residue number system"
	LANGUAGES CXX
	)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) 
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	include(CTest)

endif()

include(FetchContent)

find_package(Threads REQUIRED)
find_package(OpenMP REQUIRED)
  
add_subdirectory(src)
