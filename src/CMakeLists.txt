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

if(BUILD_MODE STREQUAL "release")

	if(LIBRARY_TYPE STREQUAL "shared")
		ADDLIB(${LIBFILE_NAME} SHARED)
	endif()
	
	if(LIBRARY_TYPE STREQUAL "static")
		ADDLIB(${LIBFILE_NAME}${LIBEXT_STATIC} STATIC)
	endif()
	
endif()

if(BUILD_MODE STREQUAL "debug")

	if(LIBRARY_TYPE STREQUAL "shared")
		ADDLIB(${LIBFILE_NAME}${LIBEXT_DEBUG} SHARED )
	endif()
	
	if(LIBRARY_TYPE STREQUAL "static")
		ADDLIB(${LIBFILE_NAME}${LIBEXT_DEBUG}${LIBEXT_STATIC} STATIC)
	endif()
	
endif()
