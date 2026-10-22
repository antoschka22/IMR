cmake_minimum_required(VERSION 3.20)
project(imr_cv CXX)

find_path(IMR_CORE_INC NAMES imr_core/version.hpp)
find_library(IMR_CORE_LIB NAMES IMRCore)

if(NOT IMR_CORE_INC OR NOT IMR_CORE_LIB)
    message(FATAL_ERROR "IMRCore library/headers not found!")
endif()

file(STRINGS "${IMR_CORE_INC}/imr_core/version.hpp" _VERSION_LINE REGEX "return \"[0-9.]+\";")
string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" IMR_CORE_VERSION "${_VERSION_LINE}")

message(STATUS "Found IMRCore version: ${IMR_CORE_VERSION}")

if(IMR_CORE_VERSION VERSION_LESS "1.0.0")
    message(FATAL_ERROR "IMRCore version too old: ${IMR_CORE_VERSION}")
endif()

add_executable(imr_cv src/main_cv.cpp)
target_include_directories(imr_cv PRIVATE ${IMR_CORE_INC})
target_link_libraries(imr_cv PRIVATE ${IMR_CORE_LIB})
