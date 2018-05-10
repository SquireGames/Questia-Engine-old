
#----------------------------------------
#				Sample sources			 
#----------------------------------------

set(QUESTIAENGINE_SAMPLE_SOURCES
    "sample.cpp"
)


#----------------------------------------
#				Create samples			 
#----------------------------------------

add_executable(sample ${QUESTIAENGINE_HEADERS} ${QUESTIAENGINE_SAMPLE_SOURCES})
target_link_libraries(sample qeng)

if(CMAKE_GENERATOR MATCHES "Visual Studio" AND NOT BUILD_SHARED_LIBS)
    target_link_libraries(sample debug MSVCRTD.lib optimized MSVCRT.lib)
endif()

set(CONAL_LIBS_NO_GTEST ${CONAN_LIBS})
list(REMOVE_ITEM CONAL_LIBS_NO_GTEST ${CONAN_LIBS_GTEST})
target_link_libraries(sample ${CONAL_LIBS_NO_GTEST})
