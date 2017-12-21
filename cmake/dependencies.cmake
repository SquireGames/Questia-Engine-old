include(downloadProject)

## force visual studio to link with /MT and MTd when linking statically
# TODO move to dependency repository
if(LIBRARY_TYPE STREQUAL "static" AND CMAKE_GENERATOR MATCHES "Visual Studio")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT" PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd" PARENT_SCOPE)
endif()


# TODO see if the project is already available on the computer

set(PROJ_NAME "qeng-deps")

downloadProject(
    PROJECT ${PROJ_NAME}
    REPOSITORY https://github.com/SquireGames/Questia-Dependencies.git
    BRANCH d240fa0
    VERSION_MAJOR 0
    VERSION_MINOR 0
)

## TODO: move to dependency repository
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# add to include path
include_directories(
    "${${PROJ_NAME}_SOURCE_DIR}/googletest/googletest/include"
    "${${PROJ_NAME}_SOURCE_DIR}/googletest/googlemock/include"
    "${${PROJ_NAME}_SOURCE_DIR}/SDL2-2.0.7/include"
)

# ensure SDL2 is compiling the correct libraries
if(BUILD_SHARED_LIBS)
    set(SDL_SHARED ON)
else()
    set(SDL_STATIC ON)
endif()

# add symlink where required for installing on linux
if(NOT WIN32)
    MACRO(ADD_SYMLINK targetLib)
        get_property(LIB_BIN_DIR TARGET ${targetLib} PROPERTY BINARY_DIR)
        get_target_property(LIB_FILE_PREFIX ${targetLib} PREFIX)
        get_target_property(LIB_FILE_BASENAME ${targetLib} OUTPUT_NAME)
        get_target_property(LIB_FILE_SUFFIX ${targetLib} SUFFIX)
        if(LIB_FILE_PREFIX MATCHES "-NOTFOUND")
            if(BUILD_SHARED_LIBS)
                set(LIB_FILE_PREFIX ${CMAKE_SHARED_LIBRARY_PREFIX})
            else()
                set(LIB_FILE_PREFIX ${CMAKE_STATIC_LIBRARY_PREFIX})
            endif()
        endif()
        if(LIB_FILE_BASENAME MATCHES "-NOTFOUND")
            set(LIB_FILE_BASENAME ${targetLib})
        endif()
        if(LIB_FILE_SUFFIX MATCHES "-NOTFOUND")
            if(BUILD_SHARED_LIBS)
                set(LIB_FILE_SUFFIX ${CMAKE_SHARED_LIBRARY_SUFFIX})
            else()
                set(LIB_FILE_SUFFIX ${CMAKE_STATIC_LIBRARY_SUFFIX})
            endif()
        endif()
        
        set(LIB_NAME_FULL ${LIB_FILE_PREFIX}${LIB_FILE_BASENAME}${LIB_FILE_SUFFIX})
        string(REGEX REPLACE "-([0-9]+)\\.([0-9]+)" "" LIB_NAME_NOVER "${LIB_NAME_FULL}")
        
        add_custom_command(
            OUTPUT ${LIB_BIN_DIR}/${LIB_NAME_NOVER}
            COMMAND ${CMAKE_COMMAND} -E create_symlink
                $<TARGET_FILE:${targetLib}>
                ${LIB_BIN_DIR}/${LIB_NAME_NOVER}
            DEPENDS ${targetLib}
        )
        add_custom_target(create_symlink_${targetLib} ALL
            DEPENDS ${LIB_BIN_DIR}/${LIB_NAME_NOVER}
        )
    ENDMACRO()

    if(SDL_SHARED)
        ADD_SYMLINK(SDL2)  
    endif()

endif()