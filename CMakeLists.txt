cmake_minimum_required(VERSION 3.10)

project(limit_order_book VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(SRC_DIR ${CMAKE_SOURCE_DIR})
set(LOB_DIR ${SRC_DIR}/LimitOrderBook)
set(TEST_DIR ${SRC_DIR}/tests)

add_executable(${PROJECT_NAME}
    ${SRC_DIR}/main.cpp
    ${LOB_DIR}/Order.cpp
    ${LOB_DIR}/Book.cpp
    ${LOB_DIR}/Limit.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${LOB_DIR})

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_NAME}")

# ====================
# Google Test Integration
# ====================

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)

FetchContent_MakeAvailable(googletest)

# Define book_test executable with additional source files for linking
add_executable(book_test 
    ${TEST_DIR}/test_book.cpp 
    ${LOB_DIR}/Order.cpp
    ${LOB_DIR}/Book.cpp
    ${LOB_DIR}/Limit.cpp
)
add_executable(redblacktree_test ${TEST_DIR}/test_redblacktree.cpp)

# Set up include directories for the tests
target_include_directories(book_test PRIVATE ${gtest_SOURCE_DIR}/googletest/include)
target_include_directories(redblacktree_test PRIVATE ${gtest_SOURCE_DIR}/googletest/include)


target_include_directories(book_test PRIVATE ${LOB_DIR})

# Link Google Test libraries
target_link_libraries(book_test gtest gtest_main)
target_link_libraries(redblacktree_test gtest gtest_main)

enable_testing()

# Add test for CTest
add_test(NAME book_test COMMAND book_test)
add_test(NAME redblacktree_test COMMAND redblacktree_test)