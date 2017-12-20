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

## TODO: remove once gtest removes the tr1 namespace
## TODO: move to dependency repository

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_definitions(-DGTEST_HAS_TR1_TUPLE=0)
add_definitions(-DGTEST_HAS_STD_TUPLE=1)

# add to include path
include_directories(
    "${${PROJ_NAME}_SOURCE_DIR}/googletest/googletest/include"
    "${${PROJ_NAME}_SOURCE_DIR}/googletest/googlemock/include"
    "${${PROJ_NAME}_SOURCE_DIR}/SDL2-2.0.7/include"
)
