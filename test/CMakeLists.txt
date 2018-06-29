
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
target_link_libraries(test_all qeng ${CONAN_LIBS})

if(CMAKE_GENERATOR MATCHES "Visual Studio" AND NOT BUILD_SHARED_LIBS)
    target_link_libraries(test_all debug MSVCRTD.lib optimized MSVCRT.lib)
endif()

add_test(NAME unit_tests COMMAND test_all)
