
cmake_minimum_required (VERSION 2.8.10)
enable_language(C CXX)

## cmake module directories
# helper modules
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

## cxx specification
set(CMAKE_CXX_STANDARD 17)

## define directory structure of output 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

## define project properties
project(QuestiaEngine)
set(QENG_VERSION_MAJOR "0")
set(QENG_VERSION_MINOR "0")
set(QENG_VERSION_PATCH "0")
set(QENG_VERSION_TWEAK "0")
set(QENG_VERSION ${QENG_VERSION_MAJOR}.${QENG_VERSION_MINOR}.${QENG_VERSION_PATCH}.${QENG_VERSION_TWEAK})

## needs to be called from top directory
enable_testing()

## include some safeguards
include(safeguards)

## get all dependencies
include(dependencies)

## define project include directories
include_directories(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_BINARY_DIR}/include
)

## generate all necessary header files
add_subdirectory(include)
## compile library
add_subdirectory(src)
## generate documentation
add_subdirectory(doc)

## run tests
add_subdirectory(test)
