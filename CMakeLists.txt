cmake_minimum_required(VERSION 3.10)

# Project name
project(BigNumProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/inc)

# Add the library
add_library(bignum src/bignum.cpp)

# Add the executable
add_executable(test test.cpp)

# Link the library to the executable
target_link_libraries(test bignum)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)