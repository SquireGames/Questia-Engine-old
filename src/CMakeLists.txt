#----------------------------------------
#				Add files				 
#----------------------------------------

## define header files
set(QUESTIAENGINE_HEADERS
	"${CMAKE_CURRENT_BINARY_DIR}/../include/${PROJECT_NAME}/config.h"
    "../include/${PROJECT_NAME}/Engine.h"
)

## define source files to compile
set(QUESTIAENGINE_SOURCES
    "Engine.cpp"
)

# allow other to get src and header files
set(QUESTIAENGINE_HEADERS ${QUESTIAENGINE_HEADERS} PARENT_SCOPE)
set(QUESTIAENGINE_SOURCES ${QUESTIAENGINE_SOURCES} PARENT_SCOPE)


#----------------------------------------
#		   Library naming scheme		 
#----------------------------------------


## naming scheme of output files
set(LIBFILE_NAME questia-eng)
set(LIBEXT_STATIC "-s")
set(LIBEXT_DEBUG "-d")


#----------------------------------------
#	    Get build and library types		 
#----------------------------------------

# convert build mode to lowercase
set(BUILD_MODE ${CMAKE_BUILD_TYPE})
string(TOLOWER "${BUILD_MODE}" BUILD_MODE)

# set default build mode if it is not set
if("${BUILD_MODE}" STREQUAL "")
	set(BUILD_MODE "both")
endif()

# if invalid buildmode print warning
if(NOT BUILD_MODE STREQUAL "debug" AND NOT BUILD_MODE STREQUAL "release" AND NOT BUILD_MODE STREQUAL "both")
	MESSAGE(STATUS "Invalid build type. Valid options: debug release both")
	PRINT(BUILD_MODE)
	MESSAGE(FATAL_ERROR)
endif()


# convert build mode to lowercase
set(LIBRARY_TYPE ${BUILD_SHARED_LIBS})
string(TOLOWER "${LIBRARY_TYPE}" LIBRARY_TYPE)

# set default build mode if it is not set
if("${LIBRARY_TYPE}" STREQUAL "")
	set(LIBRARY_TYPE "both")
elseif(${LIBRARY_TYPE} STREQUAL "on" OR ${LIBRARY_TYPE} STREQUAL "true")
	set(LIBRARY_TYPE "shared")
elseif(${LIBRARY_TYPE} STREQUAL "off" OR ${LIBRARY_TYPE} STREQUAL "false")
	set(LIBRARY_TYPE "static")
else()
	MESSAGE(STATUS "Invalid library type. Valid options: BOOL <empty>")
	PRINT(BUILD_SHARED_LIBS)
	MESSAGE(FATAL_ERROR)
endif()


#----------------------------------------
#	      Generate library files		 
#----------------------------------------


## macro to help with adding libraries
MACRO(ADDLIB libname type)
	add_library("${libname}" ${type} ${QUESTIAENGINE_SOURCES} ${QUESTIAENGINE_HEADERS})
	set_target_properties("${libname}" PROPERTIES
		VERSION ${QENG_VERSION}
	)
ENDMACRO()


## create libries with different extensions for debug and release builds
# note: header files need to be added to targets so IDE's can find them

if(BUILD_MODE STREQUAL "release" OR BUILD_MODE STREQUAL "both")

	if(LIBRARY_TYPE STREQUAL "shared" OR LIBRARY_TYPE STREQUAL "both")
		ADDLIB(${LIBFILE_NAME} SHARED)
	endif()
	
	if(LIBRARY_TYPE STREQUAL "static" OR LIBRARY_TYPE STREQUAL "both")
		ADDLIB(${LIBFILE_NAME}${LIBEXT_STATIC} STATIC)
	endif()
	
endif()


if(BUILD_MODE STREQUAL "debug" OR BUILD_MODE STREQUAL "both")

	if(LIBRARY_TYPE STREQUAL "shared" OR LIBRARY_TYPE STREQUAL "both")
		ADDLIB(${LIBFILE_NAME}${LIBEXT_DEBUG} SHARED )
	endif()
	
	if(LIBRARY_TYPE STREQUAL "static" OR LIBRARY_TYPE STREQUAL "both")
		ADDLIB(${LIBFILE_NAME}${LIBEXT_DEBUG}${LIBEXT_STATIC} STATIC)
	endif()
	
endif()
