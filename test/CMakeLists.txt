
#----------------------------------------
#				Add files				 
#----------------------------------------

include_directories("include")

## append header files
set(QUESTIAENGINE_TEST_HEADERS
    "include/QENG/Test/Test.h"
)

set(QUESTIAENGINE_TEST_SOURCES
    "Test.cpp"
)


#----------------------------------------
#				Create test			 
#----------------------------------------

add_executable(test_all ${QUESTIAENGINE_HEADERS} ${QUESTIAENGINE_TEST_SOURCES} ${QUESTIAENGINE_TEST_HEADERS})
target_link_libraries(test_all qeng gtest gmock_main)
add_test(NAME unit_tests COMMAND test_all)
