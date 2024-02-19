cmake_minimum_required(VERSION 3.27)
project(RedisLiteClient)
set(CMAKE_CXX_STANDARD 17)
# Add source files
set(SOURCES
        Client.cpp
        )

# Add header files
set(HEADERS
        Client.h
        )

## Specify header file directories
add_library(redisliteclient SHARED ${SOURCES} ${HEADERS})

