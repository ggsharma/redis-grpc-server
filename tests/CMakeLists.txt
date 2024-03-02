cmake_minimum_required(VERSION 3.27)
project(RedisGrpcTests)

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

find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)

# main executable
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# redislite library
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/cache)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/logger)



add_executable(
        logger_test
        tLogger.cpp
)
target_link_libraries(
        logger_test
        GTest::gtest_main
)

add_executable(
        cache_test
        tCache.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Cache.cpp
)
target_link_libraries(
        cache_test
        GTest::gtest_main
)

add_executable(
        controller_test
        tController.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Controller.cpp
)
target_link_libraries(
        controller_test
        grpc++_reflection
        grpc++
        GTest::gtest_main
)


include(GoogleTest)
gtest_discover_tests(controller_test)
gtest_discover_tests(logger_test)
gtest_discover_tests(cache_test)