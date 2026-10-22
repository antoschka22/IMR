cmake_minimum_required(VERSION 3.20)
project(IMRCore VERSION 1.2.3 LANGUAGES CXX)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/imr_core/version.hpp
    @ONLY
)

add_library(IMRCore SHARED src/imr_core/core.cpp)
set_target_properties(IMRCore PROPERTIES OUTPUT_NAME "IMRCore")

target_include_directories(IMRCore PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/imr_core>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS IMRCore DESTINATION lib)
install(DIRECTORY include/imr_core DESTINATION include)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/generated/imr_core/version.hpp DESTINATION include/imr_core)
