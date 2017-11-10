cmake_minimum_required (VERSION 3.0)

project (GoodCoder)

set(CMAKE_CXX_FLAGS "c++11")
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_FLAGS "-Wall")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

##########################
# Download Third Libs
##########################
## Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()
# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/libs/gtest/googletest-src
                 ${CMAKE_BINARY_DIR}/libs/gtest/googletest-build
                 EXCLUDE_FROM_ALL)

##########################
# Normal Libraries & Executables
##########################
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)
add_executable(GoodCoder ${DIR_SRCS})
add_library(dict_parser_lib ${PROJECT_SOURCE_DIR}/src/dict_parser_lib.cpp)

##########################
# Testing
##########################
enable_testing()
 
add_executable(test_dict_parser ${PROJECT_SOURCE_DIR}/test/test_dict_parser_lib.cpp)
target_link_libraries(test_dict_parser gtest gtest_main)
target_link_libraries(test_dict_parser dict_parser_lib) 
add_test(NAME mytest COMMAND test_dict_parser)
