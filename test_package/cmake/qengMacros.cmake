## set up RPATH for macos
include(setupMacosRPath)

# links qeng to an executable
macro(qeng_target_link_libraries target)
    # link qeng
    target_link_libraries(${target} qeng)
    
    # fix macos dynamic library linking issues
    fix_install_name(${target})
    
    # link proper static libraries for Visual Studio
    if(CMAKE_GENERATOR MATCHES "Visual Studio" AND NOT BUILD_SHARED_LIBS)
        target_link_libraries(${target} debug MSVCRTD.lib optimized MSVCRT.lib)
    endif()
endmacro()

# links qeng and gtest to an executable
macro(qeng_target_link_libraries_test target)
    # link qeng and gtest/gmock
    target_link_libraries(${target} qeng ${CONAN_LIBS})
    
    # fix macos dynamic library linking issues
    fix_install_name(${target})
    fix_install_name_gtest(${target})
    
    # link proper static libraries for Visual Studio
    if(CMAKE_GENERATOR MATCHES "Visual Studio" AND NOT BUILD_SHARED_LIBS)
        target_link_libraries(${target} debug MSVCRTD.lib optimized MSVCRT.lib)
    endif()
    
endmacro()

# links the target qeng lib
macro(qeng_target_link_libraries_libqeng target)
    # link conan except for GTest
    set(CONAL_LIBS_NO_GTEST ${CONAN_LIBS})
    if(CONAN_LIBS_GTEST)
        list(REMOVE_ITEM CONAL_LIBS_NO_GTEST ${CONAN_LIBS_GTEST})
    endif()
    target_link_libraries(${target} ${CONAL_LIBS_NO_GTEST})
    
    # fix macos dynamic library linking issues
    fix_install_name(${target})
endmacro()