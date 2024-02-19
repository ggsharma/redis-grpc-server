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

# Add source files
set(SOURCES
        main.cpp
        include/Controller.h src/Controller.cpp)

add_executable(redislite ${SOURCES})

# redislite search directories
include_directories(lib/server/)


# Set the directory where your dylib resides
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/server/build)

# Check the operating system and adjust the linking accordingly
if (WIN32)
    target_link_libraries(redislite  ${LIB_DIR}/libserver.dll)
elseif (APPLE)
    target_link_libraries(redislite  ${LIB_DIR}/libserver.dylib)
elseif (UNIX)
    target_link_libraries(redislite  ${LIB_DIR}/libserver.so)
endif ()


# Link the library to your executable
target_link_libraries(redislite grpc++ absl::flags absl::flags_parse)
