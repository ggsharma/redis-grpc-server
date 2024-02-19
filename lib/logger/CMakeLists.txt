cmake_minimum_required(VERSION 3.27)
project(logger)


include_directories(include)

# Add source files
set(SOURCES
        src/Server.cpp
        )

# Add header files
set(HEADERS
        include/Server.hpp
        )

## Specify header file directories
add_library(server SHARED ${SOURCES} ${HEADERS})

