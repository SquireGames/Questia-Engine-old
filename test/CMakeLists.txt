
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

add_executable(test_all ${QUESTIAENGINE_TEST_SOURCES} ${QUESTIAENGINE_TEST_HEADERS})
qeng_target_link_libraries_test(test_all)

add_test(NAME unit_tests COMMAND test_all)
