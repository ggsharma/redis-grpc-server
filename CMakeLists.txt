
cmake_minimum_required(VERSION 3.25)
project(RedisGrpcServer)

# set C++ standard
set(CMAKE_CXX_STANDARD 17)

# fetch gRPC
include(FetchContent)
set(ABSL_ENABLE_INSTALL ON)
FetchContent_GetProperties(gRPC)
if(NOT gRPC_POPULATED)
    # Fetch gRPC
    include(FetchContent)
    set(ABSL_ENABLE_INSTALL ON)
    FetchContent_Declare(
            gRPC
            GIT_REPOSITORY https://github.com/grpc/grpc
            GIT_TAG        v1.61.1
    )
#    FetchContent_MakeAvailable(gRPC)
endif()

set(FETCHCONTENT_QUIET OFF) # Cache gRPC library
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
#
add_custom_command(
        OUTPUT "${rl_proto_srcs}" "${rl_proto_hdrs}" "${rl_grpc_srcs}" "${rl_grpc_hdrs}"
        COMMAND protoc
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${rl_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${rl_proto}"
        DEPENDS "${rl_proto}")
set(PROTOBUF_GOOGLE_INCLUDE_DIR ${DEPS_DIR}/grpc-src/third_party/protobuf/src)

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
        PRIVATE
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

# redisgrpc search directories
include_directories(include/)
include_directories(lib/logger/)

add_subdirectory(lib/logger)
#add_subdirectory(tests)

# Link the library to your executable
target_link_libraries(redis_grpc_server
        PRIVATE
        logger rl_grpc_proto grpc++ absl::flags absl::flags_parse)



# Optionally, you can set gRPC-related options
set_target_properties(redis_grpc_server PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        )

# Optionally, you can install the executable
install(TARGETS redis_grpc_server
        RUNTIME DESTINATION bin
        )

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

add_executable(
        cache_test
        tests/tCache.cpp
        src/Cache.cpp
)

target_link_libraries(
        controller_test
        grpc++
        grpc++_reflection
        rl_grpc_proto
        GTest::gtest_main
)

target_link_libraries(
        cache_test
        grpc++
        grpc++_reflection
        rl_grpc_proto
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(controller_test)

#cmake_minimum_required(VERSION 3.25)
#project(RedisGrpcServer)
#
## set C++ standard
#set(CMAKE_CXX_STANDARD 17)
#
#find_package(ZLIB REQUIRED)
#
#set(ABSL_ENABLE_INSTALL ON)
#find_package(absl REQUIRED CONFIG)
##find_package(c-ares 1.13.0 REQUIRED)
#
#if(NOT ZLIB_ROOT_DIR)
#    set(ZLIB_ROOT_DIR ${CMAKE_CURRENT_BINARY_DIR}/_deps/zlib-1.3.1)
#endif()
#if(EXISTS "${ZLIB_ROOT_DIR}/CMakeLists.txt")
#    # TODO(jtattermusch): workaround for https://github.com/madler/zlib/issues/218
#    message(STATUS including zlibbbbbbbb)
#    include_directories("${ZLIB_ROOT_DIR}")
#    add_subdirectory(${ZLIB_ROOT_DIR} third_party/zlib)
#
#    if(TARGET zlibstatic)
#        set(_gRPC_ZLIB_LIBRARIES zlibstatic)
#        set(_gRPC_ZLIB_INCLUDE_DIR "${ZLIB_ROOT_DIR}")
#        message(STATUS ${_gRPC_ZLIB_INCLUDE_DIR})
##        if(gRPC_INSTALL AND _gRPC_INSTALL_SUPPORTED_FROM_MODULE)
#            install(TARGETS zlibstatic
#                    RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
#                    LIBRARY DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
#                    ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
##        endif()
#    endif()
#else()
#    message(WARNING "gRPC_ZLIB_PROVIDER is \"module\" but ZLIB_ROOT_DIR is wrong")
#endif()
#if(gRPC_INSTALL AND NOT _gRPC_INSTALL_SUPPORTED_FROM_MODULE)
#    message(WARNING "gRPC_INSTALL will be forced to FALSE because gRPC_ZLIB_PROVIDER is \"module\"  and CMake version (${CMAKE_VERSION}) is less than 3.13.")
#    set(gRPC_INSTALL FALSE)
#endif()
#
#
## Set the directory where your dependencies are located
#set(DEPS_DIR ${CMAKE_CURRENT_BINARY_DIR}/_deps)
#
#if(NOT CARES_ROOT_DIR)
#    set(CARES_ROOT_DIR ${DEPS_DIR}/cares/cares)
#endif()
##set(HAVE_LIBNSL OFF CACHE BOOL "avoid cares dependency on libnsl")
##set(CARES_SHARED OFF CACHE BOOL "disable shared library")
##set(CARES_STATIC ON CACHE BOOL "link cares statically")
##if(gRPC_BACKWARDS_COMPATIBILITY_MODE)
##    # See https://github.com/grpc/grpc/issues/17255
##    set(HAVE_LIBNSL OFF CACHE BOOL "avoid cares dependency on libnsl")
##endif()
##add_subdirectory("${CARES_ROOT_DIR}" third_party/cares/cares)
#
##if(TARGET c-ares)
#    message(STATUS inside)
#    include_directories("${CARES_ROOT_DIR}/cares/cares")
#    add_subdirectory(${CARES_ROOT_DIR} third_party/cares/cares)
#    set(_gRPC_CARES_LIBRARIES c-ares)
##    include_directories("${CARES_ROOT_DIR}/include")
##    if(gRPC_INSTALL AND _gRPC_INSTALL_SUPPORTED_FROM_MODULE)
#        install(TARGETS c-ares
#                RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
#                LIBRARY DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
#                ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
##    endif()
##endif()
#
#if(gRPC_INSTALL AND NOT _gRPC_INSTALL_SUPPORTED_FROM_MODULE)
#    message(WARNING "gRPC_INSTALL will be forced to FALSE because gRPC_CARES_PROVIDER is \"module\" and CMake version (${CMAKE_VERSION}) is less than 3.13.")
#    set(gRPC_INSTALL FALSE)
#endif()
#
#
## SSL
#
##if(TARGET absl::strings)
#message(STATUS hdkehk)
## If absl is included already, skip including it.
## (https://github.com/grpc/grpc/issues/29608)
#if(NOT ABSL_ROOT_DIR)
#    set(ABSL_ROOT_DIR ${DEPS_DIR}/abseil-cpp)
#endif()
#if(EXISTS "${ABSL_ROOT_DIR}/CMakeLists.txt")
##        if(gRPC_INSTALL)
#        # When gRPC_INSTALL is enabled and Abseil will be built as a module,
#        # Abseil will be installed along with gRPC for convenience.
#        set(ABSL_ENABLE_INSTALL ON)
##        endif()
#    add_subdirectory(${ABSL_ROOT_DIR} third_party/abseil-cpp)
#else()
#    message(WARNING "gRPC_ABSL_PROVIDER is \"module\" but ABSL_ROOT_DIR is wrong")
#endif()
##endif()
#
#
#
## Set the paths to grpc libraries and headers
#set(GRPC_INCLUDE_DIR ${DEPS_DIR}/grpc-src/include)
#set(GRPC_LIB_DIR ${DEPS_DIR}/grpc-build)
#
## Set the paths to absl libraries and headers if needed
#set(ABSL_INCLUDE_DIR ${DEPS_DIR}/grpc-src/third_party/abseil-cpp)
#set(ABSL_LIB_DIR ${DEPS_DIR}/grpc-build/third_party/abseil-cpp)
#
## Set the paths to protobuf libraries and headers
#set(PROTOBUF_INCLUDE_DIR ${DEPS_DIR}/grpc-src/third_party/protobuf)
#set(PROTOBUF_LIB_DIR ${DEPS_DIR}/grpc-build/third_party/protobuf)
#
## Set the paths to protobuf libraries and headers
#set(RE2_INCLUDE_DIR ${DEPS_DIR}/grpc-src/third_party/re2/re2)
#set(RE2_LIB_DIR ${DEPS_DIR}/grpc-build/third_party/re2)
#
#
#set(ZLIB_INCLUDE_DIR ${DEPS_DIR}/grpc-src/third_party/zlib)
#set(ZLIB_LIB_DIR ${DEPS_DIR}/grpc-build/third_party/zlib)
#
#set(CARES_INCLUDE_DIR ${DEPS_DIR}/grpc-src/third_party/cares/cares)
#set(CARES_LIB_DIR ${DEPS_DIR}/grpc-build/third_party/cares/cares)
#
#set(PROTOBUF_GOOGLE_INCLUDE_DIR ${DEPS_DIR}/grpc-src/third_party/protobuf/src)
#
#set(SSL_INCLUDE_DIR ${DEPS_DIR}/grpc-src/third_party/boringssl-with-bazel/src/include)
#set(SSL_LIB_DIR ${DEPS_DIR}/grpc-build/third_party/boringssl-with-bazel)
#
#include_directories(${PROTOBUF_GOOGLE_INCLUDE_DIR})
#
## Building the protobuf tests require gmock what is not part of a standard protobuf checkout.
## Disable them unless they are explicitly requested from the cmake command line (when we assume
## gmock is downloaded to the right location inside protobuf).
#if(NOT PROTOBUF_ROOT_DIR)
#    set(PROTOBUF_ROOT_DIR ${DEPS_DIR}/protobuf)
#endif()
#
#if(EXISTS "${PROTOBUF_ROOT_DIR}/CMakeLists.txt")
#    set(protobuf_MSVC_STATIC_RUNTIME OFF CACHE BOOL "Link static runtime libraries")
#    add_subdirectory(${PROTOBUF_ROOT_DIR} third_party/protobuf)
#    if(TARGET ${_gRPC_PROTOBUF_LIBRARY_NAME})
#        message(here)
#        set(_gRPC_PROTOBUF_LIBRARIES ${_gRPC_PROTOBUF_LIBRARY_NAME})
#    endif()
#    if(TARGET libprotoc)
#        set(_gRPC_PROTOBUF_PROTOC_LIBRARIES libprotoc)
#    endif()
#    if(TARGET protoc)
#        set(_gRPC_PROTOBUF_PROTOC protoc)
#        if(CMAKE_CROSSCOMPILING)
#            find_program(_gRPC_PROTOBUF_PROTOC_EXECUTABLE protoc)
#        else()
#            set(_gRPC_PROTOBUF_PROTOC_EXECUTABLE $<TARGET_FILE:protoc>)
#        endif()
#    endif()
#    # For well-known .proto files distributed with protobuf
#    set(_gRPC_PROTOBUF_WELLKNOWN_INCLUDE_DIR "${PROTOBUF_ROOT_DIR}/src")
#else()
#    message(WARNING "gRPC_PROTOBUF_PROVIDER is \"module\" but PROTOBUF_ROOT_DIR is wrong")
#endif()
#
#
#
#
#
#
#
## Internal proto file
#get_filename_component(rl_proto "./proto/redisgrpc.proto" ABSOLUTE)
#get_filename_component(rl_proto_path "${rl_proto}" PATH)
#
### Generated sources
#set(rl_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/redisgrpc.pb.cc")
#set(rl_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/redisgrpc.pb.h")
#set(rl_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/redisgrpc.grpc.pb.cc")
#set(rl_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/redisgrpc.grpc.pb.h")
#
#
## Add source files
#set(SOURCES
#        main.cpp
#        src/Controller.cpp
#        src/Registry.cpp
#        src/Cache.cpp
#        src/RedisGrpcServiceImpl.cpp
#        ${rl_grpc_srcs}
#        ${rl_proto_srcs})
#
## main redislite executable server
#add_executable(redis_grpc_server ${SOURCES})
#
## redislite search directories
#include_directories(include/)
#include_directories(proto/)
#include_directories(lib/logger/)
#
## Set the directory where your dylib resides
#set(LOGGER_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/logger/build)
#
#add_subdirectory(lib/logger)
#
##Include directories for grpc and absl
#target_include_directories(redis_grpc_server PRIVATE ${GRPC_INCLUDE_DIR})
## Uncomment the following line if you're using absl
#target_include_directories(redis_grpc_server PRIVATE ${ABSL_INCLUDE_DIR})
#
## Uncomment the following line if you're using absl
#target_include_directories(redis_grpc_server PRIVATE ${ABSL_INCLUDE_DIR}/absl/hash)
#
## Uncomment the following line if you're using protobuf
##target_include_directories(redis_grpc_server PRIVATE ${PROTOBUF_INCLUDE_DIR})
#
## Uncomment the following line if you're using protobuf
#target_include_directories(redis_grpc_server PRIVATE ${RE2_INCLUDE_DIR})
#
##target_include_directories(redis_grpc_server PRIVATE ${CARES_INCLUDE_DIR})
#
##
##target_include_directories(redis_grpc_server PRIVATE ${_gRPC_ZLIB_INCLUDE_DIR})
#
##target_include_directories(redis_grpc_server PRIVATE ${ZLIB_INCLUDE_DIR})
#
##target_include_directories(redis_grpc_server PRIVATE ${PROTOBUF_GOOGLE_INCLUDE_DIR})
#target_include_directories(redis_grpc_server PRIVATE ${SSL_INCLUDE_DIR})
#
## Link directories for grpc and absl
#target_link_directories(redis_grpc_server PRIVATE ${GRPC_LIB_DIR})
## Uncomment the following line if you're using absl
#target_link_directories(redis_grpc_server PRIVATE ${ABSL_LIB_DIR})
#
#target_link_directories(redis_grpc_server PRIVATE ${ABSL_LIB_DIR}/absl/hash)
#
## Uncomment the following line if you're using protobuf
##target_link_directories(redis_grpc_server PRIVATE ${PROTOBUF_LIB_DIR})
#
#target_link_directories(redis_grpc_server PRIVATE ${RE2_LIB_DIR})
#target_link_directories(redis_grpc_server PRIVATE ${SSL_LIB_DIR})
##target_link_directories(redis_grpc_server PRIVATE ${CARES_LIB_DIR})
#
##target_link_directories(redis_grpc_server PRIVATE ${_gRPC_ZLIB_LIBRARIES})
###target_link_libraries(redis_grpc_server PRIVATE ${_gRPC_ZLIB_LIBRARIES})
#
## Link grpc and absl libraries
#target_link_libraries(redis_grpc_server PRIVATE re2)
## Link grpc and absl libraries
#target_link_libraries(redis_grpc_server PRIVATE grpc++)
#
#target_link_libraries(redis_grpc_server PRIVATE zlibstatic)
#
#target_link_libraries(redis_grpc_server PRIVATE absl_hash)
#
#target_link_libraries(redis_grpc_server PRIVATE c-ares)
#
#target_link_libraries(redis_grpc_server PRIVATE ssl)
#
#target_link_libraries(redis_grpc_server PRIVATE absl::strings)
#
#target_link_libraries(redis_grpc_server PRIVATE absl::flags)
#target_link_libraries(redis_grpc_server PRIVATE absl::flags_parse)
##target_link_libraries(redis_grpc_server PRIVATE absl::lts)
#
#target_link_libraries(redis_grpc_server PRIVATE crypto)
#
##target_link_libraries(redis_grpc_server PRIVATE protobuf)
#
## Link grpc and absl libraries
#target_link_libraries(redis_grpc_server PRIVATE grpc++_reflection)

