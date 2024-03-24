cmake_minimum_required(VERSION 3.27)
project(RedisGrpcLibFileSystem)
set(CMAKE_CXX_STANDARD 17)
# Add source files
set(SOURCES
        FileSystem.cpp
        )

# Add header files
set(HEADERS
        FileSystem.h
        )

## Specify header file directories
add_library(file_system SHARED ${HEADERS} ${SOURCES})

