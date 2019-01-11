cmake_minimum_required (VERSION 3.8.2)
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
# imported from conanfile.py
option(QENG_GRAPHICS "")
option(QENG_VERSION_MAJOR "")
option(QENG_VERSION_MINOR "")
option(QENG_VERSION_PATCH "")
option(BUILD_DOC "Build Documentation" OFF)
option(QENG_BUILD_TESTS OFF)
option(QENG_BUILD_SAMPLES OFF)
# enable this if you are working from an IDE or CMake GUI that does not directly support Conan, all it does
# is import options from conanfile.py rather than from the command line
option(QENG_IMPORT_CONANFILE_DEFINES OFF)

## set static/shared settings
include(buildConfiguration)

## get dependencies
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)

# import option defines from conanfile.py
if(QENG_IMPORT_CONANFILE_DEFINES)
    foreach(DEFINE ${CONAN_DEFINES})
        string(REPLACE "-D" "" DEFINE ${DEFINE})
        string(REPLACE "=" ";\"" DEFINE ${DEFINE})
        set(DEFINE "${DEFINE}\"")
        list(GET DEFINE 0 VAR)
        list(GET DEFINE 1 VAL)
        set(${VAR} ${VAL})
    endforeach()
endif()

# set version information
set(QENG_VERSION ${QENG_VERSION_MAJOR}.${QENG_VERSION_MINOR}.${QENG_VERSION_PATCH})
set(QENG_SOVERSION ${QENG_VERSION_MAJOR}.${QENG_VERSION_MINOR})

## define helper functions to help with linking
include(qengMacros)

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
if(QENG_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

## samples
if(QENG_BUILD_SAMPLES)
    ## needs to be called from top directory
    add_subdirectory(samples)
endif()
