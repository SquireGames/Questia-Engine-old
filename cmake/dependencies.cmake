include(downloadProject)

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


# TODO make macro to automate changing output directory

# ensure install will find all lib files
set_target_properties(SDL2 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
set_target_properties(gtest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
set_target_properties(gtest_main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
set_target_properties(gmock PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
set_target_properties(gmock_main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
