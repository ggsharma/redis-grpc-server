cmake_minimum_required(VERSION 3.27)
project(logger)

# Add source files
set(SOURCES
        Logger.cpp
        )

# Add header files
set(HEADERS
        Logger.hpp
        )

## Specify header file directories
add_library(server SHARED  ${HEADERS})

