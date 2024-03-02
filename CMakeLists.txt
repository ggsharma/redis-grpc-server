cmake_minimum_required(VERSION 3.25)
project(RedisGrpcServer)

# set C++ standard
set(CMAKE_CXX_STANDARD 17)

# fetch gRPC
include(FetchContent)
set(ABSL_ENABLE_INSTALL ON)
FetchContent_Declare(
        gRPC
        GIT_REPOSITORY https://github.com/grpc/grpc
        GIT_TAG        v1.61.1
)

set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(gRPC)

option(protobuf_MODULE_COMPATIBLE TRUE)

message(STATUS "Using protobuf ${Protobuf_VERSION}")

message(STATUS "Using gRPC ${gRPC_VERSION}")

message(STATUS "Using RedisGrpc 0.1")

# Internal proto file
get_filename_component(rl_proto "./proto/redisgrpc.proto" ABSOLUTE)
get_filename_component(rl_proto_path "${rl_proto}" PATH)

# Generated sources
set(rl_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/redisgrpc.pb.cc")
set(rl_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/redisgrpc.pb.h")
set(rl_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/redisgrpc.grpc.pb.cc")
set(rl_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/redisgrpc.grpc.pb.h")

find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)

add_custom_command(
        OUTPUT "${rl_proto_srcs}" "${rl_proto_hdrs}" "${rl_grpc_srcs}" "${rl_grpc_hdrs}"
        COMMAND protoc
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${rl_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${rl_proto}"
        DEPENDS "${rl_proto}")


# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# hw_grpc_proto
add_library(rl_grpc_proto
        ${rl_grpc_srcs}
        ${rl_grpc_hdrs}
        ${rl_proto_srcs}
        ${rl_proto_hdrs})

# generate rl_grpc_proto lib
target_link_libraries(rl_grpc_proto
        grpc++_reflection
        grpc++
        libprotobuf)

# Add source files
set(SOURCES
        main.cpp
        src/Controller.cpp
        src/Registry.cpp
        src/Cache.cpp
        src/RedisGrpcServiceImpl.cpp)

# main redislite executable server
add_executable(redis_grpc_server ${SOURCES})

# redislite search directories
include_directories(include/)
#include_directories(lib/server/)
#include_directories(lib/cache/)
include_directories(lib/logger/)

# Set the directory where your dylib resides
set(LOGGER_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/logger/build)

add_subdirectory(lib/logger)

#add_subdirectory(tests)

# Link the library to your executable
target_link_libraries(redis_grpc_server logger rl_grpc_proto grpc++ absl::flags absl::flags_parse)

# Build tests
message(STATUS "Building Tests")

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(include/)


add_executable(
        controller_test
        tests/tController.cpp
        src/Registry.cpp
        src/Cache.cpp
)
target_link_libraries(
        controller_test
        grpc++
        grpc++_reflection
        rl_grpc_proto
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(controller_test)




