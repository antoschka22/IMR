cmake_minimum_required(VERSION 3.20)
project(show_image CXX)

find_package(OpenCV REQUIRED)

message(STATUS "OpenCV config file: ${OpenCV_CONFIG}")
message(STATUS "OpenCV_DIR: ${OpenCV_DIR}")
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")

add_executable(main_show_image src/main_show_image.cpp)
target_include_directories(main_show_image PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(main_show_image PRIVATE ${OpenCV_LIBS})
