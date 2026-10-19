cmake_minimum_required(VERSION 3.20)
project(imr_flat)


add_library(imr_core core.cpp)
add_executable(example example.cpp)
target_link_libraries(example PRIVATE imr_core)
