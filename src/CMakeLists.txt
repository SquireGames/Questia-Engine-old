#----------------------------------------
#			Define source files				 
#----------------------------------------

## define header files
set(QUESTIAENGINE_HEADERS
	"${CMAKE_CURRENT_BINARY_DIR}/../include/QENG/config.h"
    "../include/QENG/Engine.h"
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

# naming scheme of output library files
set(LIB_NAME qeng)
set(LIB_EXT_STATIC "-s")
set(LIB_EXT_DEBUG "-d")
# preprocessor symbol for shared library compilation
set(LIB_SYMBOL "${LIB_NAME}")
string(REPLACE "-" "_" LIB_SYMBOL "${LIB_SYMBOL}")
string(TOUPPER "LIB_SYMBOL" LIB_SYMBOL)

#----------------------------------------
#	      Create library
#----------------------------------------

if(BUILD_SHARED_LIBS)
    set(LIB_TYPE SHARED)
else()
    set(LIB_TYPE STATIC)
endif()   
 
add_library(${LIB_NAME} ${LIB_TYPE} ${QUESTIAENGINE_SOURCES} ${QUESTIAENGINE_HEADERS})

if(CMAKE_GENERATOR MATCHES "Visual Studio" AND BUILD_SHARED_LIBS)
    set_target_properties(${LIB_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set_target_properties(${LIB_NAME} PROPERTIES VERSION ${QENG_VERSION})
set_target_properties(${LIB_NAME} PROPERTIES DEFINE_SYMBOL "${LIB_SYMBOL}_EXPORTS")

if(BUILD_SHARED_LIBS)
    set_target_properties(${LIB_NAME} PROPERTIES DEBUG_POSTFIX ${LIB_EXT_DEBUG})
    if(WIN32)
        set_target_properties(${LIB_NAME} PROPERTIES SUFFIX "-${QENG_VERSION_MAJOR}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    endif()
else()
    set_target_properties(${LIB_NAME} PROPERTIES DEBUG_POSTFIX ${LIB_EXT_STATIC}${LIB_EXT_DEBUG})
    set_target_properties(${LIB_NAME} PROPERTIES RELEASE_POSTFIX ${LIB_EXT_STATIC})
    set_target_properties(${LIB_NAME} PROPERTIES MINSIZEREL_POSTFIX ${LIB_EXT_STATIC})
    set_target_properties(${LIB_NAME} PROPERTIES RELWITHDEBINFO_POSTIX ${LIB_EXT_STATIC})
endif()

set_target_properties(${LIB_NAME} PROPERTIES FOLDER "QENG")
 
# link dependencies
if(BUILD_SHARED_LIBS)
    target_link_libraries(${LIB_NAME} SDL2)
else()
    target_link_libraries(${LIB_NAME} SDL2-static)
endif()
 
# install rule
install(
    TARGETS ${LIB_NAME}
    RUNTIME DESTINATION bin COMPONENT bin
    LIBRARY DESTINATION lib${LIB_SUFFIX} COMPONENT bin
    ARCHIVE DESTINATION lib${LIB_SUFFIX} COMPONENT devel
)

 
