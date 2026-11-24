cmake_minimum_required(VERSION 3.16)
project(linuxlearn)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(file_copy FileIO_day1/file_copy.cpp)
add_executable(fork_demo Process_day2/fork_demo.cpp)
add_executable(two_child Process_day2/two_child.cpp)
