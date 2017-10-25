cmake_minimum_required (VERSION 3.0)

project (GoodCoder)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src DIR_SRCS)

add_executable(GoodCoder ${DIR_SRCS})

set(CMAKE_CXX_FLAGS "c++11")
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_FLAGS "-Wall")
