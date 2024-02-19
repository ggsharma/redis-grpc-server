cmake_minimum_required(VERSION 3.25)
project(RedisLite)

set(CMAKE_CXX_STANDARD 17)

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
find_package(Protobuf CONFIG REQUIRED)

message(STATUS "Using protobuf ${Protobuf_VERSION}")


message(STATUS "Using gRPC ${gRPC_VERSION}")

# Proto file
get_filename_component(rl_proto "./proto/redislite.proto" ABSOLUTE)
get_filename_component(rl_proto_path "${rl_proto}" PATH)

# Generated sources
set(rl_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/redislite.pb.cc")
set(rl_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/redislite.pb.h")
set(rl_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/redislite.grpc.pb.cc")
set(rl_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/redislite.grpc.pb.h")

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


target_link_libraries(rl_grpc_proto
        grpc++_reflection
        grpc++
        libprotobuf)


# Add source files
set(SOURCES
        main.cpp
        src/Controller.cpp
        src/Service.cpp)

add_executable(redislite ${SOURCES})

# redislite search directories
include_directories(include/)
include_directories(lib/server/)
include_directories(lib/cache/)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# Set the directory where your dylib resides
set(SERVER_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/server/build)
set(CACHE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/cache/build)

# Check the operating system and adjust the linking accordingly
if (WIN32)
    target_link_libraries(redislite  ${SERVER_LIB_DIR}/libserver.dll)
elseif (APPLE)
    target_link_libraries(redislite  ${SERVER_LIB_DIR}/libserver.dylib)
    target_link_libraries(redislite  ${CACHE_LIB_DIR}/libcache.dylib)
elseif (UNIX)
    target_link_libraries(redislite  ${SERVER_LIB_DIR}/libserver.so)
endif ()


# Link the library to your executable
target_link_libraries(redislite rl_grpc_proto grpc++ absl::flags absl::flags_parse)






