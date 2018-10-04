#----------------------------------------
#			Define source files				 
#----------------------------------------

## define header files
set(QUESTIAENGINE_HEADERS
        "${CMAKE_CURRENT_BINARY_DIR}/../include/QENG/config.h"
        "../include/QENG/ClientEngine.h"
        "../include/QENG/graphics/Window.h")

## define source files to compile
set(QUESTIAENGINE_SOURCES
    "ClientEngine.cpp")

## define implementations of generic classes
if(QENG_GRAPHICS MATCHES "none")
    list(APPEND QUESTIAENGINE_SOURCES
            "graphics/mock/Window.cpp")
elseif(QENG_GRAPHICS MATCHES "opengl")
    list(APPEND QUESTIAENGINE_SOURCES
            "graphics/opengl/Window.cpp")
else()
    message(FATAL_ERROR "The Graphics option: " "${QENG_GRAPHICS}" " is not currently supported.")
endif()

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

if(CMAKE_GENERATOR MATCHES "Visual Studio" AND NOT BUILD_SHARED_LIBS)
    target_link_libraries(${LIB_NAME} debug MSVCRTD.lib optimized MSVCRT.lib)
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
qeng_target_link_libraries_libqeng(${LIB_NAME})
 
# install rule
install(
    TARGETS ${LIB_NAME}
    RUNTIME DESTINATION bin COMPONENT bin
    LIBRARY DESTINATION lib${LIB_SUFFIX} COMPONENT bin
    ARCHIVE DESTINATION lib${LIB_SUFFIX} COMPONENT devel
)
