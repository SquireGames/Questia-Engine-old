
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
qeng_target_link_libraries(sample)
