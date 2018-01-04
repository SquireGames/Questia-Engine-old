include(downloadProject)

# TODO see if the project is already available on the computer

set(PROJ_NAME "qeng-deps")

downloadProject(
    PROJECT ${PROJ_NAME}
    REPOSITORY https://github.com/SquireGames/Questia-Dependencies.git
    BRANCH 97da0ba
    VERSION_MAJOR 0
    VERSION_MINOR 0
)

# add to include path
include_directories(
    "${${PROJ_NAME}_SOURCE_DIR}/googletest/googletest/include"
    "${${PROJ_NAME}_SOURCE_DIR}/googletest/googlemock/include"
    "${${PROJ_NAME}_SOURCE_DIR}/SDL2-2.0.7/include"
)

