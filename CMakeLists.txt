
cmake_minimum_required (VERSION 2.8.10)
enable_language(C CXX)

# cmake module directory
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

## c++ specification
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
set(QENG_VERSION ${QENG_VERSION_MAJOR}.${QENG_VERSION_MINOR}.${QENG_VERSION_PATCH})
set(QENG_SOVERSION ${QENG_VERSION_MAJOR}.${QENG_VERSION_MINOR})

## prevent in source builds and wrong settings
include(safeguards)

## set static/shared settings
include(buildConfiguration)

## get dependencies
include (${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

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

## testing
# disabled with shared libraries, gtest does not like to be dynamically linked on UNIX
# based systems with pthreads
option(QENG_BUILD_TESTS OFF)
if(NOT BUILD_SHARED_LIBS OR WIN32)
    if(QENG_BUILD_TESTS)
        ## needs to be called from top directory
        enable_testing()
        add_subdirectory(test)
    endif()
endif()

## samples
option(QENG_BUILD_SAMPLES OFF)
if(QENG_BUILD_SAMPLES)
    ## needs to be called from top directory
    add_subdirectory(samples)
endif()


