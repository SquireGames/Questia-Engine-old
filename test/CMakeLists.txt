
#----------------------------------------
#				Add files				 
#----------------------------------------

include_directories("include")

## append header files
set(QUESTIAENGINE_TEST_HEADERS
    ${QUESTIAENGINE_HEADERS}
    "include/${PROJECT_NAME}/Test/Test.h"
)

# TODO use QuestiaEngine lib file instead of compiling separately

## append source files
foreach(EXTSRC ${QUESTIAENGINE_SOURCES})
    LIST(APPEND QUESTIAENGINE_TEST_SOURCES "../src/${EXTSRC}")
endforeach()
   
LIST(APPEND QUESTIAENGINE_TEST_SOURCES
    "Test.cpp"
)


#----------------------------------------
#				Create test			 
#----------------------------------------

add_executable(test_all ${QUESTIAENGINE_TEST_SOURCES} ${QUESTIAENGINE_TEST_HEADERS})
target_link_libraries(test_all gtest gmock_main)
add_test(NAME test_example COMMAND test_all)

