cmake_minimum_required(VERSION 3.27)
project(RedisLiteLibCache)

# Add source files
set(SOURCES
        Cache.cpp
        )

# Add header files
set(HEADERS
        Cache.hpp
        )

## Specify header file directories
add_library(cache SHARED ${SOURCES} ${HEADERS})

