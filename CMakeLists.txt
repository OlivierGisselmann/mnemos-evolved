cmake_minimum_required(VERSION 3.25)

project(MnemosEvolved VERSION 0.0.1 DESCRIPTION "Mnemos Engine Rewrite")

# Set language standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O2")

# Create shared library
add_library(${PROJECT_NAME} SHARED
    engine/engine.cpp
    engine/core/logging/log.cpp
)

# Export additional .lib file for windows symbols
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Set project version
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

# Set public API header
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/mnemos.hpp)

# Include sources and public API to avoid relative paths
target_include_directories(${PROJECT_NAME} PRIVATE engine)
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Add application subfolder
add_subdirectory(application)