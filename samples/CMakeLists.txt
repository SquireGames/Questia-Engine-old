
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

target_link_libraries(sample)
