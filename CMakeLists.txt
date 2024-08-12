cmake_minimum_required(VERSION 3.9)
project(lab3)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab3 src/main.cpp src/lab3.cpp src/lab3.h)

target_link_libraries(lab3)

