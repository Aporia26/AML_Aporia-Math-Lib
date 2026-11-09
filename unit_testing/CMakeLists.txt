cmake_minimum_required(VERSION 3.24)
project(AML_Tests LANGUAGES CXX)

# Force lightning-fast Release optimizations (O3 speed tuning)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Speed optimization flags for MinGW
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-pipe -O3 -march=native)
elseif(MSVC)
    add_compile_options(/MP /O2)
endif()

# Output the aml_tests.exe binary directly into your current AML directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# Explicitly target your actual test file name
add_executable(aml_tests "${CMAKE_CURRENT_SOURCE_DIR}/AML_Tests.cpp")

# Modern CMake best-practice include routing:
# 1. Adds the current folder so headers like #include "Vector.hpp" work.
# 2. Adds the parent directory so headers like #include "aml/aml.hpp" work if your folder is named 'aml'.
get_filename_component(PARENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" DIRECTORY)
target_include_directories(aml_tests PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${PARENT_DIR}"
)
