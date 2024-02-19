cmake_minimum_required(VERSION 3.27)
project(server)

include_directories(include)

# Add source files
set(SOURCES
        Server.cpp
        )

# Add header files
set(HEADERS
        Server.hpp
        )

## Specify header file directories
add_library(server SHARED ${SOURCES} ${HEADERS})

