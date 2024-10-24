cmake_minimum_required(VERSION 3.10)

# Project name and version
project(limit_order_book VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Define source directories
set(SRC_DIR ${CMAKE_SOURCE_DIR})
set(LOB_DIR ${SRC_DIR}/LimitOrderBook)
set(TEST_DIR ${SRC_DIR}/tests)  # Directory for tests

# Add executable target for main program
add_executable(${PROJECT_NAME}
    ${SRC_DIR}/main.cpp
    ${LOB_DIR}/Order.cpp
    ${LOB_DIR}/Book.cpp
    ${LOB_DIR}/Limit.cpp
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${LOB_DIR})

# Define cleaning target (optional, but nice to have)
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_NAME}")

# ====================
# Google Test Integration
# ====================

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# Prevent Google Test from overriding compiler options
FetchContent_MakeAvailable(googletest)

# Add test executable for RedBlackTree testing
add_executable(redblacktree_test ${TEST_DIR}/test_redblacktree.cpp)

# Include directories for test
target_include_directories(redblacktree_test PRIVATE ${gtest_SOURCE_DIR}/googletest/include)

# Link Google Test libraries to the test executable
target_link_libraries(redblacktree_test gtest gtest_main)

# Enable testing
enable_testing()

# Add test to CMake's testing framework
add_test(NAME redblacktree_test COMMAND redblacktree_test)