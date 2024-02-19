cmake_minimum_required(VERSION 3.27)
project(RedisLiteTests)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

# main executable
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# redislite library
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/cache)

add_executable(
        controller_test
        tController.cpp
)
target_link_libraries(
        controller_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(controller_test)