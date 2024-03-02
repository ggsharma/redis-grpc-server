#cmake_minimum_required(VERSION 3.27)
#project(RedisGrpcTests)
#
#message(STATUS "Building Tests")
#
## GoogleTest requires at least C++17
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
#
#include(FetchContent)
#
#
#FetchContent_Declare(
#        googletest
#        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
#)
## For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)
#
#set(ABSL_ENABLE_INSTALL ON)
#FetchContent_Declare(
#        gRPC
#        GIT_REPOSITORY https://github.com/grpc/grpc
#        GIT_TAG        v1.61.1
#)
#
#set(FETCHCONTENT_QUIET OFF)
#FetchContent_MakeAvailable(gRPC)
#
#option(protobuf_MODULE_COMPATIBLE TRUE)
#
#message(STATUS "Using protobuf ${Protobuf_VERSION}")
#
#message(STATUS "Using gRPC ${gRPC_VERSION}")
#
#message(STATUS "Using RedisGrpc 0.1")
#option(protobuf_MODULE_COMPATIBLE TRUE)
#
#enable_testing()
#
## main executable
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
#
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib/logger)
#
#
#
##add_executable(
##        logger_test
##        tLogger.cpp
##)
##target_link_libraries(
##        logger_test
##        GTest::gtest_main
##)
##
##add_executable(
##        cache_test
##        tCache.cpp
##        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Cache.cpp
##)
##target_link_libraries(
##        cache_test
##        GTest::gtest_main
##)
##set(PROTO_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../build)
### Check the operating system and adjust the linking accordingly
##if (WIN32)
##    target_link_libraries(rl_grpc_proto  ${PROTO_LIB_DIR}/librl_grpc_proto.dll)
##    message(STATUS "libproto built")
##elseif (APPLE)
##    target_link_libraries(rl_grpc_proto  ${PROTO_LIB_DIR}/librl_grpc_proto.a)
##    message(STATUS "libproto built")
##elseif (UNIX)
##    target_link_libraries(redislite  ${PROTO_LIB_DIR}/librl_grpc_proto.so)
##    message(STATUS "libproto built")
##endif ()
## Generated sources
#set(rl_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/../../build/redisgrpc.pb.cc")
#set(rl_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/../../build/redisgrpc.pb.h")
#set(rl_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/../../build/redisgrpc.grpc.pb.cc")
#set(rl_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/../../build/redisgrpc.grpc.pb.h")
#
## hw_grpc_proto
#add_library(rl_grpc_proto
#        ${rl_grpc_srcs}
#        ${rl_grpc_hdrs}
#        ${rl_proto_srcs}
#        ${rl_proto_hdrs})
#
#
#add_executable(
#        controller_test
#        tController.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Registry.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Cache.cpp
#)
#
#target_link_libraries(
#        controller_test
#        redis_grpc_server
#        grpc++
#        grpc++_reflection
#        rl_grpc_proto
#        GTest::gtest_main
#)
#
#
#include(GoogleTest)
#gtest_discover_tests(controller_test)
##gtest_discover_tests(logger_test)
##gtest_discover_tests(cache_test)