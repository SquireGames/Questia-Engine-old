#----------------------------------------
#	    Build Mode
#----------------------------------------

# ensure CMAKE_BUILD_TYPE option exists
set(CMAKE_BUILD_TYPE "debug" CACHE STRING "release or dubug")

# convert build mode to lowercase
set(BUILD_MODE ${CMAKE_BUILD_TYPE})
string(TOLOWER "${BUILD_MODE}" BUILD_MODE)

# set default build mode if it is not set
if("${BUILD_MODE}" STREQUAL "")
	set(BUILD_MODE "release")
endif()

# if invalid buildmode print warning
if(NOT BUILD_MODE STREQUAL "debug" AND NOT BUILD_MODE STREQUAL "release")
	MESSAGE(STATUS "Invalid build type. Valid options: debug release")
	MESSAGE(STATUS "${BUILD_MODE}")
	MESSAGE(FATAL_ERROR)
endif()

# only allow debug or release modes
if(BUILD_MODE STREQUAL "release")
    set(CMAKE_CONFIGURATION_TYPES "Release")
endif()
if(BUILD_MODE STREQUAL "debug")
    set(CMAKE_CONFIGURATION_TYPES "Debug")
endif()

#----------------------------------------
#	    Library Type
#----------------------------------------

# ensure the BUILD_SHARED_LIBS option exists
option(BUILD_SHARED_LIBS OFF)

# convert build mode to lowercase
set(LIBRARY_TYPE ${BUILD_SHARED_LIBS})
string(TOLOWER "${LIBRARY_TYPE}" LIBRARY_TYPE)

# set default build mode if it is not set
if(${LIBRARY_TYPE} STREQUAL "on" OR ${LIBRARY_TYPE} STREQUAL "true")
	set(LIBRARY_TYPE "shared")
elseif(${LIBRARY_TYPE} STREQUAL "" OR ${LIBRARY_TYPE} STREQUAL "off" OR ${LIBRARY_TYPE} STREQUAL "false")
	set(LIBRARY_TYPE "static")
else()
	MESSAGE(STATUS "Invalid library type. Valid options: ON OFF")
	MESSAGE(STATUS "${BUILD_SHARED_LIBS}")
	MESSAGE(FATAL_ERROR)
endif()

#----------------------------------------
#	      Compiler options	 
#----------------------------------------

## force visual studio to link with /MT and MTd when linking statically

# TODO move responsibility to questia dependencies repository

if(LIBRARY_TYPE STREQUAL "static")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

