cmake_minimum_required(VERSION 3.20)
project(imr_cv CXX)

option(PATHS_HARD_CODED "Use hardcoded relative paths" OFF)
option(PATHS_WITH_FIND  "Use find_path and find_library" OFF)
option(PATHS_IMPORTED   "Use imported targets" OFF)
option(PATHS_SYSTEM     "Use system paths" OFF)


set(MODE_COUNT 0)
if(PATHS_HARD_CODED)
    math(EXPR MODE_COUNT "${MODE_COUNT} + 1")
endif()
if(PATHS_WITH_FIND)
    math(EXPR MODE_COUNT "${MODE_COUNT} + 1")
endif()
if(PATHS_IMPORTED)
    math(EXPR MODE_COUNT "${MODE_COUNT} + 1")
endif()
if(PATHS_SYSTEM)
    math(EXPR MODE_COUNT "${MODE_COUNT} + 1")
endif()

if(MODE_COUNT EQUAL 0)
    message(WARNING "No path mode selected! Defaulting behavior may fail.")
elseif(NOT MODE_COUNT EQUAL 1)
    message(FATAL_ERROR "Exactly one PATHS_* option must be ON!")
endif()

add_executable(imr_cv src/apps/main_cv.cpp)

if(PATHS_HARD_CODED)
    target_include_directories(imr_cv PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../imr_core/include)
    target_link_libraries(imr_cv PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../imr_core/build/lib/libimr_core.so)
endif()

if(PATHS_WITH_FIND)
    find_path(IMR_CORE_INCLUDE_DIR NAMES imr_core/core.hpp)
    find_library(IMR_CORE_LIB NAMES imr_core)
    target_include_directories(imr_cv PRIVATE ${IMR_CORE_INCLUDE_DIR})
    target_link_libraries(imr_cv PRIVATE ${IMR_CORE_LIB})
endif()

if(PATHS_IMPORTED)
    find_path(IMR_INC imr_core/core.hpp)
    find_library(IMR_LIB imr_core)
    add_library(imr_core_imported SHARED IMPORTED)
    set_target_properties(imr_core_imported PROPERTIES
        IMPORTED_LOCATION "${IMR_LIB}"
        INTERFACE_INCLUDE_DIRECTORIES "${IMR_INC}"
    )
    target_link_libraries(imr_cv PRIVATE imr_core_imported)
endif()

if(PATHS_SYSTEM)
    target_compile_definitions(imr_cv PRIVATE PATHS_SYSTEM)
    find_path(SYS_IMR_INC NAMES imr_core/core.hpp PATHS ${CMAKE_PREFIX_PATH}/include)
    find_library(SYS_IMR_LIB NAMES imr_core PATHS ${CMAKE_PREFIX_PATH}/lib)

    if(NOT SYS_IMR_INC OR NOT SYS_IMR_LIB)
        message(FATAL_ERROR "Could not find imr_core under ${CMAKE_PREFIX_PATH}! INC: ${SYS_IMR_INC}, LIB: ${SYS_IMR_LIB}")
    endif()

    target_include_directories(imr_cv PRIVATE ${SYS_IMR_INC})
    target_link_libraries(imr_cv PRIVATE ${SYS_IMR_LIB})
endif()
