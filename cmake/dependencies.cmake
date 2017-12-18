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
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(GTEST_HAS_TR1_TUPLE 0 PARENT_SCOPE)
set(GTEST_HAS_STD_TUPLE 1 PARENT_SCOPE)

# add to include path
include_directories(
    "${${PROJ_NAME}_SOURCE_DIR}/googletest/googletest/include"
    "${${PROJ_NAME}_SOURCE_DIR}/googletest/googlemock/include"
    "${${PROJ_NAME}_SOURCE_DIR}/SDL2-2.0.7/include"
)
