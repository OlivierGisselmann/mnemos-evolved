# Project settings
cmake_minimum_required(VERSION 3.25)
cmake_policy(VERSION 3.18)
project(MnemosEvolved VERSION 0.0.1 DESCRIPTION "Mnemos Engine Rewrite")
enable_language(C)
enable_language(CXX)

# Set language standard
set(CMAKE_SUPPRESS_REGENERATION ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(PLATFORM_WINDOWS)
    # Create shared library
    add_library(${PROJECT_NAME} SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/engine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/core/logging/log.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/core/timer/timer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/debug/debug.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/platform/window/win32/window.cpp
    )

    # Export additional .lib file for windows symbols
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_definitions(-DMEXPORT)

    # Set project version
    set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
    set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

    # Set public API header
    set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/mnemos.hpp)

    # Include sources and public API to avoid relative paths
    target_include_directories(${PROJECT_NAME} PRIVATE engine)
    target_include_directories(${PROJECT_NAME} PRIVATE include)
elseif(PLATFORM_LINUX)
    # Create shared library
    add_library(${PROJECT_NAME} SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/engine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/core/logging/log.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/core/timer/timer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/debug/debug.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/platform/window/x11/window.cpp
    )

    add_definitions(-DMEXPORT)

    # Set project version
    set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
    set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

    # Set public API header
    set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/mnemos.hpp)

    # Include sources and public API to avoid relative paths
    target_include_directories(${PROJECT_NAME} PRIVATE engine)
    target_include_directories(${PROJECT_NAME} PRIVATE include)
endif()

# Add application subfolder
add_subdirectory(application)